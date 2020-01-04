#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;
using namespace sf;

constexpr int WINDOW_WIDTH{800}, WINDOW_HEIGHT{600};
constexpr float BULL_RADIUS{10.f}, VELOCITY{300.f}, BOOST_COEFF{20.f};
constexpr float PABBLE_WIDTH{60.f}, PABBLE_HEIGHT{20.f}, PABBLE_VELOCITY{200.f};
constexpr float BLOCK_WIDTH{60.f}, BLOCK_HEIGHT{20.f};
constexpr float POPUP_X{400.f}, POPUP_Y{300.f};
constexpr float MESS_POINTS_X{20.f}, MESS_POINTS_Y{620.f}, MESS_LEVEL_X{250.f}, MESS_LEVEL_Y{620.f};
constexpr float GAME_INSTRUCTION_X{400.f}, GAME_INSTRUCTION_Y{380.f};
constexpr float WELL_WIDTH{800.f}, WELL_HEIGHT{5.f};
constexpr int COUNT_BLOCKS_X{11}, COUNT_BLOCKS_Y{4}, POINT{10}, LEVEL{1}, WINNING_LEVEL{9}, INDENT{60};
const string STR_FONT{"font/17853.ttf"};
const string dirText[] = {"Player points: ", "Player level: ", "left key - moving the platform to the left", "right key - moving the platform to the right", "space - pause / start", "L-Ctrl - start over"};
const string dirImg[] = {"images/ball.png", "images/paddle.png", "images/brick.png", "images/arkanoid.jpg", "images/game_over.jpg", "images/victory.jpg"};
enum textureId
{
    BALL,
    PADDLE,
    BRICK,
    ARKANOID,
    GAME_OVER,
    VICTORY
};
enum textId
{
    POINT_TEXT,
    LEVEL_TEXT,
    LEFT_KEY,
    RIGHT_KEY,
    SPACE,
    L_CONTROL
};

struct Ball
{
    Texture texture;
    CircleShape shape;
    Vector2f velocity{-VELOCITY, -VELOCITY};
    float boost = VELOCITY;
    bool statusBall{false};

    void loadTexture(const Texture &ballTexture, float mX, float mY)
    {
        texture.setSmooth(true);
        shape.setTexture(&ballTexture);
        shape.setPosition(mX, mY);
        shape.setRadius(BULL_RADIUS);
        shape.setOrigin(BULL_RADIUS, BULL_RADIUS);
    }

    float gatDirection() { return boost; }
    bool getStatusBall() { return statusBall; }

    void setStatusBall(bool stat) { statusBall = stat; }
    void setTheStartingPosition(float mX, float mY) { shape.setPosition(mX, mY); }
    void setTheStartingBoost()
    {
        boost = VELOCITY;
        velocity.x = -boost;
        velocity.y = -boost;
    }
    void setBoostBall(int levelIndex)
    {
        boost = boost + levelIndex * BOOST_COEFF;
        cout << "Ball_boost: " << boost << endl;
        velocity.x = -boost;
        velocity.y = -boost;
    }

    void update(const float dt)
    {
        Vector2f position = shape.getPosition();
        position += velocity * dt;

        if ((position.x + BULL_RADIUS >= WINDOW_WIDTH) && (velocity.x > 0))
            velocity.x = -velocity.x;
        if ((position.x - BULL_RADIUS < 0) && (velocity.x < 0))
            velocity.x = -velocity.x;
        if ((position.y + BULL_RADIUS >= WINDOW_HEIGHT) && (velocity.y > 0))
        {
            velocity.y = -velocity.y;
            setStatusBall(true);
        }
        if ((position.y - BULL_RADIUS < 0) && (velocity.y < 0))
            velocity.y = -velocity.y;
        shape.setPosition(position);
    }

    float sideLeft() { return shape.getPosition().x - shape.getRadius(); }
    float sideRight() { return shape.getPosition().x + shape.getRadius(); }
    float sideUp() { return shape.getPosition().y - shape.getRadius(); }
    float sideBown() { return shape.getPosition().y + shape.getRadius(); }
};

struct Paddle
{
    Texture texture;
    RectangleShape shape;
    Vector2f velocity;
    float boost = VELOCITY;

    void loadTexture(const Texture &paddleTexture, float mX, float mY)
    {
        texture.setSmooth(true);
        shape.setTexture(&paddleTexture);
        shape.setPosition(mX, mY);
        shape.setSize({PABBLE_WIDTH, PABBLE_HEIGHT});
        shape.setOrigin(PABBLE_WIDTH / 2.f, PABBLE_HEIGHT / 2.f);
    }

    void update(const float dt)
    {
        Vector2f position = shape.getPosition();
        position += velocity * dt;
        float step = shape.getSize().x / 2.f;

        if (Keyboard::isKeyPressed(Keyboard::Key::Left) && (position.x - step > 0))
            velocity.x = -boost;
        else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && (position.x + step < WINDOW_WIDTH))
            velocity.x = boost;
        else
            velocity.x = 0;
        shape.setPosition(position);
    }

    float gatDirection() { return boost; }

    void setTheStartingPosition(float mX, float mY) { shape.setPosition(mX, mY); }
    void setTheStartingBoost() { boost = VELOCITY; }
    void setBoostPaddle(int levelIndex)
    {
        boost = boost + levelIndex * BOOST_COEFF;
        velocity.x = -boost;
    }

    float sideLeft() { return shape.getPosition().x - shape.getSize().x / 2.f; }
    float sideRight() { return shape.getPosition().x + shape.getSize().x / 2.f; }
    float sideUp() { return shape.getPosition().y - shape.getSize().y / 2.f; }
    float sideBown() { return shape.getPosition().y + shape.getSize().y / 2.f; }
};

struct Brick
{
    Texture texture;
    RectangleShape shape;
    bool destroyed{false};

    Brick(const Texture &brickTexture, float mX, float mY)
    {
        texture.setSmooth(true);
        shape.setTexture(&brickTexture);
        shape.setPosition(mX, mY);
        shape.setSize({BLOCK_WIDTH, BLOCK_HEIGHT});
        shape.setFillColor(Color::White);
        shape.setOrigin(BLOCK_WIDTH / 2.f, BLOCK_HEIGHT / 2.f);
    }

    float sideLeft() { return shape.getPosition().x - shape.getSize().x / 2.f; }
    float sideRight() { return shape.getPosition().x + shape.getSize().x / 2.f; }
    float sideUp() { return shape.getPosition().y - shape.getSize().y / 2.f; }
    float sideBown() { return shape.getPosition().y + shape.getSize().y / 2.f; }
};

struct Progress
{
    int playerPoints{0};
    int playerLevel{1};
    bool victory{false};

    bool getStatusVictory() { return victory; }
    int getPlayerPoints() { return playerPoints; }
    int getPlayerLevel() { return playerLevel; }

    void addPoint(int point) { playerPoints += point; }
    void addLevel(int level) { playerLevel += level; }

    void setStatusVictory(bool stat) { victory = stat; }

    bool checkVictory()
    {
        if (playerLevel == WINNING_LEVEL)
        {
            victory = true;
            return true;
        }
        else
            return false;
    }

    void initialValue()
    {
        playerPoints = 0;
        playerLevel = 1;
    }
};

struct PopUp
{
    Texture texture;
    Sprite sprite;

    void loadTexture(const Texture &popUpTexture, float mX, float mY)
    {
        texture.setSmooth(true);
        sprite.setTexture(popUpTexture);
        sprite.setPosition(mX, mY);
        Rect<float> size = sprite.getGlobalBounds();
        sprite.setOrigin(Vector2f(size.width / 2, size.height / 2));
    }
};

struct TextMessage
{
    Font font;
    Text text;

    void loadTextProperties(const string &myFont, float mX, float mY, int size = 20)
    {
        if (!font.loadFromFile(myFont))
        {
            cout << "Error loading file" << endl;
            exit(1);
        }
        text.setFont(font);
        text.setFillColor(Color::White); //покрасили текст в любой цвет. если убрать эту строку, то по умолчанию он белый
        text.setStyle(Text::Regular);    //жирный и подчеркнутый текст. по умолчанию он тонкий и не подчеркнутый
        text.setCharacterSize(size);
        text.setPosition(mX, mY); //задаем позицию текста, центр камеры
    }

    void updateGameText(const string &path, int number)
    {
        ostringstream playerScoreString;
        playerScoreString << number;
        text.setString(path + playerScoreString.str());
    }

    void instructionText(const string &path, const string &myFont, float mX, float mY, int size = 20)
    {
        if (!font.loadFromFile(myFont))
        {
            cout << "Error loading file" << endl;
            exit(1);
        }
        text.setFont(font);
        text.setString(path);
        text.setFillColor(Color::White); //покрасили текст в любой цвет. если убрать эту строку, то по умолчанию он белый
        text.setStyle(Text::Regular);    //жирный и подчеркнутый текст. по умолчанию он тонкий и не подчеркнутый
        text.setCharacterSize(size);
        text.setPosition(mX, mY); //задаем позицию текста, центр камеры
        Rect<float> str = text.getGlobalBounds();
        text.setOrigin(Vector2f(str.width / 2, str.height / 2));
    }
};

struct GameText
{
    map<int, string> m_text;

    void loadMyText(map<int, string> &myMap, int key, const string &path) { myMap.emplace(key, path); }

    GameText()
    {
        int sizeVecText = sizeof(dirText) / sizeof(dirText[0]);
        for (int index = 0; index < sizeVecText; index++)
            loadMyText(m_text, index, dirText[index]);
    }

    string &getTextFor(const int &key) { return m_text.at(key); }
};

struct GameTextures
{
    map<int, Texture> m_textures;

    void loadMyTexture(map<int, Texture> &myMap, int key, const string &path)
    {
        Texture myTexture;
        if (!myTexture.loadFromFile(path))
        {
            cout << "Error loading file" << endl;
            exit(1);
        }
        myTexture.loadFromFile(path);
        myMap.emplace(key, myTexture);
    }

    GameTextures()
    {
        int sizeVecTex = sizeof(dirImg) / sizeof(dirImg[0]);
        for (int index = 0; index < sizeVecTex; index++)
            loadMyTexture(m_textures, index, dirImg[index]);
    }

    Texture &getTextureFor(const int &key) { return m_textures.at(key); }
};

struct Wall
{
    RectangleShape shape;
    void loadWall(int mX, int mY)
    {
        shape.setPosition(mX, mY);
        shape.setSize({WELL_WIDTH, WELL_HEIGHT});
        shape.setFillColor(Color::White);
    }
};

struct World
{
    Ball ball;
    Paddle paddle;
    vector<Brick> bricks;
    Wall wall;

    bool pause{true};
    bool restart{false};

    bool getStatusPause() { return pause; }
    bool getStatusRestart() { return restart; }

    void setStatusPause(bool stat) { pause = stat; }
    void setStatusRestart(bool stat) { restart = stat; }
};

struct Message
{
    PopUp winPause;
    PopUp winGameOv;
    PopUp winVictory;

    TextMessage infoPoints;
    TextMessage infoLevel;
    TextMessage infoMoveLeft;
    TextMessage infoMoveRight;
    TextMessage infoPause;
    TextMessage infoRestart;
};

template <class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
    return mA.sideRight() >= mB.sideLeft() && mA.sideLeft() <= mB.sideRight() &&
           mA.sideBown() >= mB.sideUp() && mA.sideUp() <= mB.sideBown();
}

void testCollision(Paddle &mPaddle, Ball &mBall)
{
    if (!isIntersecting(mPaddle, mBall))
        return;

    mBall.velocity.y = -(mBall.gatDirection());

    if (mBall.shape.getPosition().x < mPaddle.shape.getPosition().x)
        mBall.velocity.x = -(mBall.gatDirection());
    else
        mBall.velocity.x = mBall.gatDirection();
}

void testCollision(Brick &mBrick, Ball &mBall)
{
    if (!isIntersecting(mBrick, mBall))
        return;

    mBrick.destroyed = true;

    float overlapLeft{mBall.sideRight() - mBrick.sideLeft()};
    float overlapRight{mBrick.sideRight() - mBall.sideLeft()};
    float overlapTop{mBall.sideBown() - mBrick.sideUp()};
    float overlapBottom{mBrick.sideBown() - mBall.sideUp()};

    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if (abs(minOverlapX) < abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -(mBall.gatDirection()) : mBall.gatDirection();
    else
        mBall.velocity.y = ballFromTop ? -(mBall.gatDirection()) : mBall.gatDirection();
}

void updatePoints(Brick &mBrick, Ball &mBall, Progress &mProgPoints)
{
    if (!isIntersecting(mBrick, mBall))
        return;
    mProgPoints.addPoint(POINT);
}

void updateLevel(World &mWorld, Progress &mProgLevel)
{
    if (mWorld.bricks.size() == 0)
        mProgLevel.addLevel(LEVEL);
}

bool defeat(World &mW)
{
    return (mW.getStatusRestart() && mW.ball.getStatusBall()) ? true : false;
}

bool nextLevel(World &mW)
{
    return mW.bricks.size() == 0 ? true : false;
}

void updateBoostBall(World &mWorld, Progress &mProgress)
{
    if (nextLevel(mWorld))
    {
        mWorld.ball.setBoostBall(mProgress.getPlayerLevel());
        mWorld.paddle.setBoostPaddle(mProgress.getPlayerLevel());
    }
}

void returnInitialValues(World &mW)
{
    mW.ball.setTheStartingPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    mW.ball.setStatusBall(false); //переводим в статус: шарик НЕпотерян
    mW.paddle.setTheStartingPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);
}

void returnInitialValues(Progress &mP)
{
    mP.initialValue(); //возвращаем стартовые значения прогресса
}

void retuenInitalBoost(World &mW)
{
    mW.ball.setTheStartingBoost();
    mW.paddle.setTheStartingBoost();
}

void initBricks(World &mW, GameTextures &mT)
{
    for (int iX{0}; iX < COUNT_BLOCKS_X; ++iX)
        for (int iY{0}; iY < COUNT_BLOCKS_Y; ++iY)
            mW.bricks.emplace_back(mT.getTextureFor(BRICK), ((iX + 1) * (BLOCK_WIDTH + 3) + 22), ((iY + 2) * (BLOCK_HEIGHT + 3)));
}

void removeBricks(World &mW)
{
    mW.bricks.clear();
}

void updateBricks(World &mWorld, Progress &mProgress, GameTextures &mTextures)
{
    if (nextLevel(mWorld) || defeat(mWorld))
    {
        if (defeat(mWorld))
        {
            returnInitialValues(mProgress);
            retuenInitalBoost(mWorld);
        }

        returnInitialValues(mWorld); // вернуть шар и платформу в исходное место
        removeBricks(mWorld);
        initBricks(mWorld, mTextures); // инициализация кирпичей IMG_BRICK
    }
    mWorld.setStatusRestart(false);
}

void updateObjects(World &mWorld, Progress &mProgress, float myDeltaTime)
{
    mWorld.ball.update(myDeltaTime);
    mWorld.paddle.update(myDeltaTime);
    testCollision(mWorld.paddle, mWorld.ball);

    for (auto &brick : mWorld.bricks)
    {
        testCollision(brick, mWorld.ball);
        updatePoints(brick, mWorld.ball, mProgress);
    }

    mWorld.bricks.erase(remove_if(begin(mWorld.bricks), end(mWorld.bricks), [](const Brick &mBrick) { return mBrick.destroyed; }), end(mWorld.bricks));
}

void updateText(Message &mMessage, GameText &mText, Progress &mProgress)
{
    mMessage.infoPoints.updateGameText(mText.getTextFor(POINT_TEXT), mProgress.getPlayerPoints());
    mMessage.infoLevel.updateGameText(mText.getTextFor(LEVEL_TEXT), mProgress.getPlayerLevel());
}

void updateDate(World &myWorld, Progress &myProgress, Message &myMessage, GameText &myText, GameTextures &myTextures, Clock &clock)
{
    const float deltaTime = clock.restart().asSeconds();

    updateLevel(myWorld, myProgress);
    updateBoostBall(myWorld, myProgress);
    updateBricks(myWorld, myProgress, myTextures);
    updateText(myMessage, myText, myProgress);

    if (myWorld.getStatusPause() || myWorld.ball.getStatusBall() || myProgress.checkVictory())
        return;

    updateObjects(myWorld, myProgress, deltaTime);
}

void initObjects(World &myWorld, GameTextures &myTextures)
{
    myWorld.ball.loadTexture(myTextures.getTextureFor(BALL), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    myWorld.paddle.loadTexture(myTextures.getTextureFor(PADDLE), WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);
    initBricks(myWorld, myTextures);
    myWorld.wall.loadWall(0, WINDOW_HEIGHT + 2);
}

void initWinMessege(Message &mMessage, GameTextures &mTextures)
{
    mMessage.winPause.loadTexture(mTextures.getTextureFor(ARKANOID), POPUP_X, POPUP_Y);
    mMessage.winGameOv.loadTexture(mTextures.getTextureFor(GAME_OVER), POPUP_X, POPUP_Y);
    mMessage.winVictory.loadTexture(mTextures.getTextureFor(VICTORY), POPUP_X, POPUP_Y);
}

void initProgressMessege(Message &mMessage)
{
    mMessage.infoPoints.loadTextProperties(STR_FONT, MESS_POINTS_X, MESS_POINTS_Y);
    mMessage.infoLevel.loadTextProperties(STR_FONT, MESS_LEVEL_X, MESS_LEVEL_Y);
}

void initInfoMessege(Message &mMessage, GameText &mText)
{
    mMessage.infoMoveLeft.instructionText(mText.getTextFor(LEFT_KEY), STR_FONT, GAME_INSTRUCTION_X, GAME_INSTRUCTION_Y);
    mMessage.infoMoveRight.instructionText(mText.getTextFor(RIGHT_KEY), STR_FONT, GAME_INSTRUCTION_X, GAME_INSTRUCTION_Y + 20.f);
    mMessage.infoPause.instructionText(mText.getTextFor(SPACE), STR_FONT, GAME_INSTRUCTION_X, GAME_INSTRUCTION_Y + 40.f);
    mMessage.infoRestart.instructionText(mText.getTextFor(L_CONTROL), STR_FONT, GAME_INSTRUCTION_X, GAME_INSTRUCTION_Y + 20.f);
}

void initMessage(Message &myMessage, GameText &myText, GameTextures &myTextures)
{
    initWinMessege(myMessage, myTextures);
    initProgressMessege(myMessage);
    initInfoMessege(myMessage, myText);
}

void pollEvents(World &myWorld, RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window.close();
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Space)
                myWorld.pause = !myWorld.pause;
            if (event.key.code == Keyboard::RControl)
                myWorld.setStatusRestart(true);
            break;
        default:
            break;
        }
    }
}

void redrawWorld(World &myWorld, Progress &myProg, Message &myMes, RenderWindow &window)
{
    window.setFramerateLimit(120);
    window.clear(Color::Black);
    window.draw(myWorld.ball.shape);
    window.draw(myWorld.paddle.shape);
    window.draw(myWorld.wall.shape);
    window.draw(myMes.infoPoints.text);
    window.draw(myMes.infoLevel.text);
    for (auto &brick : myWorld.bricks)
        window.draw(brick.shape);
    if (myWorld.getStatusPause())
    {
        window.draw(myMes.winPause.sprite);
        window.draw(myMes.infoMoveLeft.text);
        window.draw(myMes.infoMoveRight.text);
        window.draw(myMes.infoPause.text);
    }
    if (myWorld.ball.getStatusBall())
    {
        window.draw(myMes.winGameOv.sprite);
        window.draw(myMes.infoRestart.text);
    }
    if (myProg.getStatusVictory())
        window.draw(myMes.winVictory.sprite);
    window.display();
}

int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT + INDENT), "Arkanoid");
    Clock clock;

    GameTextures gameTextures;
    GameText gameText;
    World world;
    Progress progress;
    Message message;

    initObjects(world, gameTextures);
    initMessage(message, gameText, gameTextures);

    while (window.isOpen())
    {
        pollEvents(world, window);
        updateDate(world, progress, message, gameText, gameTextures, clock);
        redrawWorld(world, progress, message, window);
    }
    return 0;
}