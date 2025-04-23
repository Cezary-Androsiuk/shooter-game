#include "DefeatState.h"

#include "utils/Constants.h"
#include "utils/Support.h"
#include "utils/GlobalData.h"

void DefeatState::initBlurredPlayBackgroundSprite()
{
    if(!m_blurredPlayBackgroundLoaded)
    {
        printf("skipping initialization of blurred play background in Defeat stage\n");
        fflush(stdout);
        return;
    }

    sf::Vector2u textureSize = m_blurredPlayBackgroundTexture.getSize();
    m_blurredPlayBackgroundSprite = std::make_unique<sf::Sprite>(
        m_blurredPlayBackgroundTexture,
        sf::IntRect(0,0, textureSize.x, textureSize.y));
    /// scale not required, because image size if for sure size of the window

    /// but sprite require vertical flip, due to Image mechanic
    m_blurredPlayBackgroundSprite->setScale(1.f, -1.f);
    m_blurredPlayBackgroundSprite->setPosition(0, textureSize.y);
}

void DefeatState::initBackgroundSprite()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_backgroundSprite = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getDefeatStateBackgroundTexture(),
        sf::IntRect(0,0, 1920, 1080));
    m_backgroundSprite->setScale(windowRatio);
}

void DefeatState::initExitPlayButton()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    m_exitPlayButton = std::make_unique<Button>();
    m_exitPlayButton->setPosition(sf::Vector2f((840.f+5) *windowRatio.x, (630.f+5) *windowRatio.y));
    m_exitPlayButton->setSize(sf::Vector2f((236.f-10) *windowRatio.x, (62.f-10) *windowRatio.y));

    m_exitPlayButton->setColor(ELEMENT_COLOR_IDLE);
    m_exitPlayButton->setColorHover(ELEMENT_COLOR_HOVER);
    m_exitPlayButton->setColorPress(ELEMENT_COLOR_PRESS);
}

void DefeatState::initStats()
{
    m_moneyLabel = std::make_unique<sgui::Label>();
    m_moneyLabel->setFont(GlobalData::getInstance()->getFontInkFree());
    m_moneyLabel->setCharacterSize(20);

    m_timeLabel = std::make_unique<sgui::Label>();
    m_timeLabel->setFont(GlobalData::getInstance()->getFontInkFree());
    m_timeLabel->setCharacterSize(20);

    this->refreshStats();
}

void DefeatState::intMargin()
{
    const sf::Vector2f &windowSize = GlobalData::getInstance()->getWindowSize();
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();

    // float thickness = 100;
    // float thicknessX = thickness * windowRatio.x;
    // float thicknessY = thickness * windowRatio.y;

    // m_margin.top.setSize(sf::Vector2f(windowSize.x, thicknessY));
    // m_margin.left.setSize(sf::Vector2f(thicknessX, windowSize.y));
    // m_margin.bottom.setSize(sf::Vector2f(windowSize.x, thicknessY));
    // m_margin.right.setSize(sf::Vector2f(thicknessX, windowSize.y));

    // m_margin.top.setPosition(sf::Vector2f(0.f, 0.f));
    // m_margin.left.setPosition(sf::Vector2f(0.f, 0.f));
    // m_margin.bottom.setPosition(sf::Vector2f(0.f, windowSize.y - thicknessX));
    // m_margin.right.setPosition(sf::Vector2f(windowSize.x - thicknessX, 0.f));

    // m_margin.top.setFillColor(WINDOW_BACKGROUND_SF_COLOR);
    // m_margin.left.setFillColor(WINDOW_BACKGROUND_SF_COLOR);
    // m_margin.bottom.setFillColor(WINDOW_BACKGROUND_SF_COLOR);
    // m_margin.right.setFillColor(WINDOW_BACKGROUND_SF_COLOR);

    /// NOTCH
    m_statInfoNotch = std::make_unique<sf::Sprite>(
        GlobalData::getInstance()->getPlayStatInfoNotchTexture(),
        sf::IntRect(0,0, 800, 90));
    m_statInfoNotch->setScale(windowRatio);
    m_statInfoNotch->setPosition(sf::Vector2f((1920.f/2 - 800.f/2) * windowRatio.x, 0.f ));

}

DefeatState::DefeatState()
    : m_blurredPlayBackgroundLoaded{false}
{

}

DefeatState::~DefeatState()
{

}

void DefeatState::init()
{
    this->initBlurredPlayBackgroundSprite();
    this->initBackgroundSprite();
    this->initExitPlayButton();
    this->initStats();
    this->intMargin();
}

bool DefeatState::requestExitPlay()
{
    return m_exitPlayButton->getClick();
}

void DefeatState::pollEvent(const sf::Event &event)
{
    m_exitPlayButton->event(event);
}

void DefeatState::update()
{
    m_exitPlayButton->update();
}

void DefeatState::render(sf::RenderTarget *target)
{
    if(m_blurredPlayBackgroundLoaded)
        target->draw(*m_blurredPlayBackgroundSprite);

    target->draw(*m_statInfoNotch);
    // target->draw(m_margin.top);
    // target->draw(m_margin.left);
    // target->draw(m_margin.bottom);
    // target->draw(m_margin.right);

    target->draw(*m_backgroundSprite);

    m_exitPlayButton->render(target);

    m_moneyLabel->render(target);
    m_timeLabel->render(target);
}

void DefeatState::setBlurredPlayBackgroundImage(const sf::Image &image)
{
    if(!m_blurredPlayBackgroundTexture.loadFromImage(image))
    {
        fprintf(stderr, "failed to load blurred play background from image\n");
        fflush(stderr);
        m_blurredPlayBackgroundLoaded = false;
    }
    m_blurredPlayBackgroundLoaded = true;
}

void DefeatState::setEarnedMoney(float earnedMoney)
{
    m_earnedMoney = earnedMoney;
}

void DefeatState::setSurvivedSeconds(int survivedSeconds)
{
    m_survivedSeconds = survivedSeconds;
}

void DefeatState::refreshStats()
{
    const sf::Vector2f &windowRatio = GlobalData::getInstance()->getWindowRatio();
    constexpr int bufferSize = 32;
    char snOut[bufferSize] = {0};
    int requiredSize;

    /// set text
    m_earnedMoney = round(m_earnedMoney * 100) / 100.f; /// to make sure, but shoud be rounded
    requiredSize = snprintf(snOut, bufferSize, "Money: %d$", (int)m_earnedMoney);
    Support::informAboutToSmallBuffer(requiredSize, bufferSize);
    m_moneyLabel->setString(snOut);

    /// set text
    int secondsElapsed = m_survivedSeconds % 60;
    int minutesElapsed = secondsElapsed / 60;
    requiredSize = snprintf(snOut, bufferSize, "Time: %02d:%02ds",
                            minutesElapsed, secondsElapsed);
    Support::informAboutToSmallBuffer(requiredSize, bufferSize);
    m_timeLabel->setString(snOut);


    /// set size
    sf::Vector2f moneyLabelSize = m_moneyLabel->getSize();
    m_moneyLabel->setPosition(
        sf::Vector2f((1920.f/2) * windowRatio.x -moneyLabelSize.x/2,
                     (1080.f/2 - 65.f) * windowRatio.y));

    /// set size
    sf::Vector2f timeLabelSize = m_timeLabel->getSize();
    m_timeLabel->setPosition(
        sf::Vector2f((1920.f/2) * windowRatio.x -timeLabelSize.x/2,
                     (1080.f/2 +10.f) * windowRatio.y));
}

void DefeatState::disableBlurredPlayBackground()
{
    m_blurredPlayBackgroundLoaded = false;
}
