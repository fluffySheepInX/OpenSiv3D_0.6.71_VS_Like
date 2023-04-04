# include <Siv3D.hpp> // OpenSiv3D v0.6.7

// ウィンドウの幅
const double WindowSizeWidth = 1200;
// ウィンドウの高さ
const double WindowSizeHeight = 800;
// マップの幅
int mapWidth = -1;
// マップの高さ
int mapHeight = -1;
// プレイヤーのサイズ(幅)
const int PlayerWidth = 50;
// プレイヤーのサイズ(高さ)
const int PlayerHeight = 50;
const String PathImage = U"image001";
const String PathMusic = U"music001";
const String PathSound = U"sound001";

enum Language {
	English,
	Japan,
	C
};
enum GameMode {
	Game,
	Menu,
	Lan,
	Option,
	Exit
};

/// @brief 弾情報クラス
struct Bullet
{
	/// @brief 中心座標
	Vec2 pos;

	/// @brief 半径
	double radius;

	/// @brief 向き（正規化済）
	Vec2 direction;

	/// @brief 早さ（ピクセル毎秒）
	double speed;

	/// @brief 色
	ColorF color;

	/// @brief ダメージ量
	int32 damage;

	/// @brief 弾生存フラグ
	bool isAlive = true;

	/// @brief 弾の Circle を返す関数
	/// @return Circle
	Circle getCircle() const
	{
		return Circle{ pos, radius };
	}

	/// @brief 弾を描画する関数
	void draw() const
	{
		getCircle().draw(color);
	}
};
/// @brief 敵クラス
struct Enemy
{
	/// @brief 体力
	int HP = 0;
	/// @brief 生存しているかどうか
	bool isAlive = true;
	/// @brief 幅
	double width = 0;
	/// @brief 高さ
	double height = 0;
	/// @brief 早さ（ピクセル毎秒）
	double speed;

	Vec2 pos;

	RectF getRect()
	{
		return RectF{ Arg::center(pos.x, pos.y), width, height };
	}
};

class WindowManager {

public:
	Language language = Language::English;
	double bgmValue = 5.0;

public:
	GameMode ShowSelectLangWindow()
	{
		// ウィンドウのタイトル | Window title
		Window::SetTitle(U"MagicAr-Ver0.1");
		// ウィンドウのサイズ | Window size
		Window::Resize(WindowSizeWidth, WindowSizeHeight);
		//// フルスクリーンモードのデフォルトを有効にするか | Whether to enable fullscreen mode by default
		//Window::SetFullscreen(true);
		// 背景の色を設定する | Set the background color
		Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
		// フレームレートの上限を設定する | Set the frame rate limit

		// ウィンドウを中心に移動
		Window::Centering();
		//ウィンドウを手動でリサイズできるようにする
		Window::SetStyle(WindowStyle::Sizable);
		//仮想ウィンドウサイズが新しいシーンのサイズになります
		Scene::SetResizeMode(ResizeMode::Virtual);

		// 画像を使用する為のTexture宣言
		String lan = PathImage + U"/btnLanguage.png";
		const Texture textureSiv3DKun{ lan, TextureDesc::Unmipped };
		const int width = 270;
		const int height = 100;
		const int centerHeight = (WindowSizeHeight / 2) - (height / 2);
		const int centerWidth = (WindowSizeWidth / 2) - (width / 2);
		//第1引数x座標,第2引数y座標,第3引数幅,第4引数高さ
		const Rect rectSiv3DKun{ centerWidth , centerHeight - 300,width,height };
		// フォントを作成
		const Font font{ 40 };
		// font を使って text を pos の位置に描画したときのテキストの領域を取得
		String text = U"English";
		String text2 = U"日本語";
		RectF rectText = font(text).region();
		RectF rectText2 = font(text2).region();
		RectF rect = { (WindowSizeWidth / 2) - (rectText.w / 2), 300,rectText.w,60 };
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), 370,rectText2.w,60 };

		while (System::Update())
		{
			//draw群
			{
				rectSiv3DKun(textureSiv3DKun).draw();
				rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(U"English").draw((WindowSizeWidth / 2) - (rectText.w / 2), 300, ColorF{ 0.25 });
				font(U"日本語").draw((WindowSizeWidth / 2) - (rectText2.w / 2), 370, ColorF{ 0.25 });
			}

			//押されたら次の画面へ進む
			if (rect.leftClicked())
			{
				language = English;
				break;
			}
			if (rect2.leftClicked())
			{
				language = Japan;
				break;
			}
		}
		return Menu;
	}
	GameMode ShowMenu()
	{
		const Font font{ 40 };
		String text = U"";
		String textSelectLang = U"";
		String textOption = U"";
		String textExit = U"";
		switch (language)
		{
		case English:
			text += U"Go hunt";
			textSelectLang += U"SelectLang";
			textOption += U"Option";
			textExit += U"Game end";
			break;
		case Japan:
			text += U"狩りへ行く";
			textSelectLang += U"言語選択";
			textOption += U"設定";
			textExit += U"ゲーム終了";
			break;
		case C:
			break;
		default:
			break;
		}
		int height = 100;
		int height2 = 200;
		int height3 = 300;
		int height4 = 400;
		RectF rectText = font(text).region();
		RectF rect = { (WindowSizeWidth / 2) - (rectText.w / 2), height,rectText.w,60 };
		RectF rectText2 = font(textSelectLang).region();
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };
		RectF rectText3 = font(textOption).region();
		RectF rect3 = { (WindowSizeWidth / 2) - (rectText3.w / 2), height3,rectText3.w,60 };
		RectF rectText4 = font(textExit).region();
		RectF rect4 = { (WindowSizeWidth / 2) - (rectText4.w / 2), height4,rectText4.w,60 };

		GameMode ga = Game;
		while (System::Update())
		{
			//draw
			{
				rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(text).draw((WindowSizeWidth / 2) - (rectText.w / 2), height, ColorF{ 0.25 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textSelectLang).draw((WindowSizeWidth / 2) - (rectText2.w / 2), height2, ColorF{ 0.25 });
				rect3.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textOption).draw((WindowSizeWidth / 2) - (rectText3.w / 2), height3, ColorF{ 0.25 });
				rect4.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textExit).draw((WindowSizeWidth / 2) - (rectText4.w / 2), height4, ColorF{ 0.25 });
			}

			//押されたら画面遷移
			if (rect.leftClicked())
			{
				ga = Game;
				break;
			}
			if (rect2.leftClicked())
			{
				ga = Lan;
				break;
			}
			if (rect3.leftClicked())
			{
				ga = Option;
				break;
			}
			if (rect4.leftClicked())
			{
				ga = Exit;
				break;
			}
		}

		return ga;
	}
	GameMode ShowOption(Audio& audio)
	{
		const Font font{ 40 };

		String textBGM = U"";
		String textBackMenu = U"";

		switch (language)
		{
		case English:
			textBGM += U"BGM volume";
			textBackMenu += U"Back to menu";
			break;
		case Japan:
			textBGM += U"BGM音量";
			textBackMenu += U"メニューへ戻る";
			break;
		case C:
			break;
		default:
			break;
		}

		int height = 100;
		int height2 = 200;
		RectF rectRegionTextBGM = font(textBGM).region();
		RectF rectTextBGM = { (WindowSizeWidth / 2) - (rectRegionTextBGM.w / 2) - 150, height,rectRegionTextBGM.w,60 };

		RectF rectText2 = font(textBackMenu).region();
		RectF rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };

		GameMode ga = Game;

		while (System::Update())
		{
			//draw
			{
				//rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textBGM).draw((WindowSizeWidth / 2) - (rectRegionTextBGM.w / 2) - 150, height, ColorF{ 0.25 });
				rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
				font(textBackMenu).draw((WindowSizeWidth / 2) - (rectText2.w / 2), height2, ColorF{ 0.25 });
			}

			if (SimpleGUI::SliderAt(U"{:.2f}"_fmt(bgmValue), bgmValue, 0.0, 10.0, Vec2{ (WindowSizeWidth / 2) + (rectRegionTextBGM.w / 2), height + rectRegionTextBGM.h / 2 }))
			{
				// 音量を設定
				audio.setVolume(bgmValue);
			}

			if (rect2.leftClicked())
			{
				ga = Menu;
				break;
			}

		}
		return ga;
	}
	GameMode PlayGame()
	{
		const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
		// 絵文字からテクスチャを作成する | Create a texture from an emoji
		const Texture texturePlayer{ U"🦖"_emoji };
		const Texture textureEnemy{ U"🦖"_emoji };
		//texturePlayer.resized(PlayerWidth);
		// マップ画像を使用する為のTexture宣言
		const Texture textureMap{ PathImage + U"/map.png", TextureDesc::Mipped };
		mapWidth = textureMap.width();
		mapHeight = textureMap.height();
		//textureMap.resized(mapWidth);
		// プレイヤーの移動スピード | Player's movement speed
		double speed = 600.0;
		// プレイヤーが右を向いているか | Whether player is facing right
		bool isPlayerFacingRight = true;
		// プレイヤーの位置
		Vec2 playerPos(WindowSizeWidth / 2, WindowSizeHeight / 2);
		Vec2 centerPos(WindowSizeWidth / 2, WindowSizeHeight / 2);
		Array<Bullet> bullets;
		Array<Enemy> enemies;

		int counter = -1;
		while (System::Update())
		{
			if (counter > 600)
			{
				counter = 0;
			}
			counter++;

			const ScopedRenderStates2D sampler{ SamplerState::RepeatLinear };

			//draw
			{
				// マップを描く | Draw the map
				DrawMap(playerPos, textureMap, font);

				// プレイヤーを描く | Draw the player
				DrawPlayer(texturePlayer, isPlayerFacingRight, playerPos);

				// 弾を描画する
				DrawBullets(bullets);
				// 弾情報を更新する
				UpdateBullets(bullets, Scene::DeltaTime());

				if (counter == 300 || counter == 0)
				{
					// 敵情報を生成する
					CreateEnemy(enemies);
				}
				// 敵を描画する
				DrawEnemy(textureEnemy, enemies);
				// 敵情報を更新する
				UpdateEnemies(enemies, Scene::DeltaTime(), playerPos);

				CheckPlayerBulletEnemyCollision(bullets, enemies);
			}

			{
				// Aキーが押されていたら | If A key is pressed
				if (KeyA.pressed())
				{
					// プレイヤーが左に移動する | Player moves left
					playerPos.x = (playerPos.x + speed * Scene::DeltaTime());
					isPlayerFacingRight = false;
				}

				// Sキーが押されていたら | If S key is pressed
				if (KeyS.pressed())
				{
					// プレイヤーが下に移動する | Player moves bottom
					playerPos.y = (playerPos.y - speed * Scene::DeltaTime());
				}

				// Dキーが押されていたら | If D key is pressed
				if (KeyD.pressed())
				{
					// プレイヤーが右に移動する | Player moves right
					playerPos.x = (playerPos.x - speed * Scene::DeltaTime());
					isPlayerFacingRight = true;
				}

				// Wキーが押されていたら | If W key is pressed
				if (KeyW.pressed())
				{
					// プレイヤーが上に移動する | Player moves up
					playerPos.y = (playerPos.y + speed * Scene::DeltaTime());
				}

				// マウスの左ボタンが押されていたら
				if (MouseL.pressed())
				{
					// マウスの位置を取得する | Gets the mouse position
					Vec2 mousePos = Cursor::Pos();

					// マウスの位置に向かって弾を発射する// Fires the bullet towards the mouse position
					FireBullet(centerPos, mousePos, bullets);
				}
			}
		}
		return Menu;
	}
private:
	void ShowConfigWindowTest()
	{
		// ウィンドウのタイトル | Window title
		Window::SetTitle(U"TestGame-Ver0.1");
		// ウィンドウのサイズ | Window size
		Window::Resize(1200, 800);
		//// フルスクリーンモードのデフォルトを有効にするか | Whether to enable fullscreen mode by default
		//Window::SetFullscreen(true);
		// 背景の色を設定する | Set the background color
		Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
		// フレームレートの上限を設定する | Set the frame rate limit

		// ウィンドウを中心に移動
		Window::Centering();
		//ウィンドウを手動でリサイズできるようにする
		Window::SetStyle(WindowStyle::Sizable);
		//仮想ウィンドウサイズが新しいシーンのサイズになります
		Scene::SetResizeMode(ResizeMode::Virtual);

		// 画像を使用する為のTexture宣言
		const Texture textureSiv3DKun{ U"example/siv3d-kun.png", TextureDesc::Mipped };

		// 
		const int pointOneX = 500;
		const int pointOneY = 60;
		const Polygon hexagonOne = Shape2D::Hexagon(60, Vec2{ pointOneX, pointOneY });
		const Vec2 offsetOne = Vec2(pointOneX, pointOneY);

		while (System::Update())
		{
			{
				// Polygon に対し、(35, 180) を画像の中心とするようにテクスチャを貼り付けて描画
				hexagonOne.draw(HSV{ 240, 0.5, 1.0 });
				hexagonOne.toBuffer2D(Arg::center = (Vec2{ 35, 180 } + offsetOne), textureSiv3DKun.size())
					.draw(textureSiv3DKun);
			}

			//hexagonが押されたら次の画面へ進む
			if (hexagonOne.leftClicked())
			{
				break;
			}
		}
	}
	GameMode PlayGameTest()
	{
		const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
		// 絵文字からテクスチャを作成する | Create a texture from an emoji
		const Texture texturePlayer{ U"🦖"_emoji };
		//texturePlayer.resized(PlayerWidth);
		// マップ画像を使用する為のTexture宣言
		const Texture textureMap{ PathImage + U"/map.png", TextureDesc::Mipped };
		mapWidth = textureMap.width();
		mapHeight = textureMap.height();
		//textureMap.resized(mapWidth);
		// プレイヤーの移動スピード | Player's movement speed
		double speed = 600.0;
		// プレイヤーが右を向いているか | Whether player is facing right
		bool isPlayerFacingRight = true;
		// プレイヤーの位置
		Vec2 playerPos(WindowSizeWidth / 2, WindowSizeHeight / 2);

		while (System::Update())
		{
			//draw
			{
				// マップを描く | Draw the map
				DrawMap(playerPos, textureMap, font);

				// プレイヤーを描く | Draw the player
				DrawPlayer(texturePlayer, isPlayerFacingRight, playerPos);
			}

			{
				// Aキーが押されていたら | If A key is pressed
				if (KeyA.pressed())
				{
					// プレイヤーが左に移動する | Player moves left
					playerPos.x = Max((playerPos.x - speed * Scene::DeltaTime()), WindowSizeWidth / 2 - (mapWidth / 2));
					isPlayerFacingRight = false;
				}

				// Sキーが押されていたら | If S key is pressed
				if (KeyS.pressed())
				{
					// プレイヤーが下に移動する | Player moves bottom
					playerPos.y = Min((playerPos.y + speed * Scene::DeltaTime()), (WindowSizeHeight / 2) + (mapHeight / 2));
					isPlayerFacingRight = true;
				}

				// Dキーが押されていたら | If D key is pressed
				if (KeyD.pressed())
				{
					// プレイヤーが右に移動する | Player moves right
					playerPos.x = Min((playerPos.x + speed * Scene::DeltaTime()), (WindowSizeWidth / 2) + (mapWidth / 2));
					isPlayerFacingRight = true;
				}

				// Wキーが押されていたら | If W key is pressed
				if (KeyW.pressed())
				{
					// プレイヤーが上に移動する | Player moves up
					playerPos.y = Max((playerPos.y - speed * Scene::DeltaTime()), (WindowSizeHeight / 2) - (mapHeight / 2));
					isPlayerFacingRight = true;
				}
			}
		}
		return Menu;
	}

	/// @brief 弾の移動と削除を行います。
	/// @param bullets 弾の配列
	/// @param deltaTime 経過時間
	void UpdateBullets(Array<Bullet>& bullets, double deltaTime)
	{
		for (auto& bullet : bullets)
		{
			bullet.pos += (bullet.direction * bullet.speed * deltaTime);
		}

		// 画面外の弾を削除
		bullets.remove_if([](const Bullet& b)
			{
				return (not b.getCircle().intersects(Scene::Rect()));
			});
	}

	void UpdateEnemies(Array<Enemy>& enemies, double deltaTime, Vec2 playerPos)
	{
		for (auto& enemy : enemies)
		{
			Vec2 direction = (playerPos - enemy.pos).normalized();
			enemy.pos += (direction * enemy.speed * deltaTime);
		}

		// 死んだ敵を削除
		enemies.remove_if([](const Enemy& e)
			{
				return (e.isAlive == false);
			});
	}
	void CreateEnemy(Array<Enemy>& enemies)
	{
		Enemy enemy;
		enemy.HP = 10;
		enemy.speed = 10;
		enemy.height = 50;
		enemy.width = 50;
		enemy.pos = Vec2{ 30,30 };
		enemies.push_back(enemy);
	}
	// Fires the bullet towards the mouse position
	void FireBullet(Vec2 playerPos, Vec2 mousePos, Array<Bullet>& bullets)
	{
		Bullet bullet;
		bullet.pos = playerPos;
		bullet.direction = (mousePos - playerPos).normalized();
		bullet.speed = 200;
		bullet.radius = 10.0;
		bullet.color = Palette::Red;
		bullet.damage = 10;
		bullets.push_back(bullet);
	}
	/// @brief 弾を描画します
	/// @param bullets 弾の配列
	void DrawBullets(Array<Bullet>& bullets)
	{
		for (const auto& bullet : bullets)
		{
			bullet.draw();
		}
	}
	/// @brief マップを描画します
	/// @param playerPos 自機の位置
	/// @param mapTexture マップ画像
	/// @param font フォント
	void DrawMap(Vec2 playerPos, Texture mapTexture, Font font)
	{
		// 差分を計算する
		double x = playerPos.x - WindowSizeWidth / 2;
		double y = playerPos.y - WindowSizeHeight / 2;

		// マップの左上の位置を計算する
		Vec2 mapPos = Vec2(-x + (-(mapWidth / 2) + WindowSizeWidth / 2), -y + (-(mapHeight / 2) + WindowSizeHeight / 2));

		mapTexture(mapPos.x, mapPos.y, mapWidth, mapHeight).draw();
	}
	void DrawMapTest(Vec2 playerPos, Texture mapTexture, Font font)
	{
		// 差分を計算する
		double x = playerPos.x - WindowSizeWidth / 2;
		double y = playerPos.y - WindowSizeHeight / 2;

		// マップの左上の位置を計算する
		Vec2 mapPos = Vec2(-x + (-(mapWidth / 2) + WindowSizeWidth / 2), -y + (-(mapHeight / 2) + WindowSizeHeight / 2));

		// マップを描画する
		mapTexture.draw(mapPos);
	}
	/// @brief プレイヤーを描画します
	/// @param playerTexture 自機画像
	/// @param isPlayerFacingRight 自機向きのフラグ
	void DrawPlayer(Texture playerTexture, bool isPlayerFacingRight, Vec2 playerPos)
	{
		playerTexture
			.scaled(1)
			.mirrored(isPlayerFacingRight)
			.draw((WindowSizeWidth / 2) - PlayerWidth, (WindowSizeHeight / 2) - PlayerHeight);
	}
	/// @brief 敵を描画します
	/// @param enemyTexture 敵画像
	void DrawEnemy(Texture enemyTexture, Array<Enemy>& enemies)
	{
		for (auto& enemy : enemies)
		{
			enemyTexture
				.scaled(0.5)
				.drawAt(enemy.pos);
		}
	}

	/// @brief プレイヤーの弾と敵の当たり判定を行います
	/// @param bullets 弾の配列
	/// @param enemies 敵の配列
	void CheckPlayerBulletEnemyCollision(Array<Bullet>& bullets, Array<Enemy>& enemies)
	{
		for (auto& bullet : bullets)
		{
			for (auto& enemy : enemies)
			{
				if (bullet.getCircle().intersects(enemy.getRect()))
				{
					enemy.HP -= bullet.damage;
					bullet.isAlive = false;
					if (enemy.HP <= 0)
					{
						enemy.isAlive = false;
					}
				}
			}
		}
	}

};


// メイン関数 | Main function
void Main()
{
	// 音声ファイルを読み込み
	String lan = PathMusic + U"/PreparationBattle001.wav";
	// Audio を作成
	Audio audio{ lan };
	// 再生
	audio.play();

	// 画面管理クラスの宣言
	std::shared_ptr<WindowManager> windowManager = std::make_shared<WindowManager>();
	// 初期画面は言語選択画面
	GameMode ga = windowManager->ShowSelectLangWindow();
	// ループのフラグ
	bool checkLoop = true;
	// 初期画面の次はメニュー画面
	ga = windowManager->ShowMenu();

	while (checkLoop and System::Update())
	{
		switch (ga)
		{
		case Game:
			// ゲーム本編
			ga = windowManager->PlayGame();
			break;
		case Menu:
			// メニュー画面
			ga = windowManager->ShowMenu();
			break;
		case Lan:
			// 言語選択画面
			ga = windowManager->ShowSelectLangWindow();
			break;
		case Option:
			// オプション画面
			ga = windowManager->ShowOption(audio);
			break;
		case Exit:
			// 終了
			checkLoop = false;
			// BGM終了
			audio.stop();
			break;
		default:
			break;
		}
	}
}
