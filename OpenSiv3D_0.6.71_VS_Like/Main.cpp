# include <Siv3D.hpp> // OpenSiv3D v0.6.7

enum Language {
	English,
	Japan,
	C
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
// 共有するデータ
struct GameData
{
	Audio audio;
};

using App = SceneManager<String, GameData>;

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

double bgmValue = 5.0;
Language language;


// 言語選択シーン
class SelectLang : public App::Scene
{
public:
	// コンストラクタ（必ず実装）
	SelectLang(const InitData& init)
		: IScene{ init }
	{
		language = Language::English;

		// 画像を使用する為のTexture宣言
		String lan = PathImage + U"/btnLanguage.png";
		textureSiv3DKun = Texture{ lan, TextureDesc::Unmipped };
		String text = U"English";
		String text2 = U"日本語";
		// font を使って text を pos の位置に描画したときのテキストの領域を取得
		rectText = font(text).region();
		rectText2 = font(text2).region();
		rect = { (WindowSizeWidth / 2) - (rectText.w / 2), 300,rectText.w,60 };
		rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), 370,rectText2.w,60 };
	}

	// 更新関数（オプション）
	void update() override
	{
		//押されたら次の画面へ進む
		if (rect.leftClicked())
		{
			language = English;
			// 遷移
			changeScene(U"Title", 0.3s);
		}
		if (rect2.leftClicked())
		{
			language = Japan;
			// 遷移
			changeScene(U"Title", 0.3s);
		}
	}

	// 描画関数（オプション）
	void draw() const override
	{
		rectSiv3DKun(textureSiv3DKun).draw();
		rect.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
		rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
		font(U"English").draw((WindowSizeWidth / 2) - (rectText.w / 2), 300, ColorF{ 0.25 });
		font(U"日本語").draw((WindowSizeWidth / 2) - (rectText2.w / 2), 370, ColorF{ 0.25 });
	}
private:
	Texture textureSiv3DKun;
	const int width = 270;
	const int height = 100;
	const int centerHeight = (WindowSizeHeight / 2) - (height / 2);
	const int centerWidth = (WindowSizeWidth / 2) - (width / 2);
	//第1引数x座標,第2引数y座標,第3引数幅,第4引数高さ
	const Rect rectSiv3DKun{ centerWidth , centerHeight - 300,width,height };
	// フォントを作成
	const Font font{ 40 };
	RectF rectText;
	RectF rectText2;
	RectF rect;
	RectF rect2;
};
// タイトルシーン
class Title : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	Title(const InitData& init)
		: IScene{ init }
	{
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

		rectText = font(text).region();
		rect = { (WindowSizeWidth / 2) - (rectText.w / 2), height,rectText.w,60 };
		rectText2 = font(textSelectLang).region();
		rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };
		rectText3 = font(textOption).region();
		rect3 = { (WindowSizeWidth / 2) - (rectText3.w / 2), height3,rectText3.w,60 };
		rectText4 = font(textExit).region();
		rect4 = { (WindowSizeWidth / 2) - (rectText4.w / 2), height4,rectText4.w,60 };
	}

	// 更新関数（オプション）
	void update() override
	{
		//押されたら画面遷移
		if (rect.leftClicked())
		{
			// 遷移
			changeScene(U"PlayGame", 0.3s);
		}
		if (rect2.leftClicked())
		{
			// 遷移
			changeScene(U"SelectLang", 0.3s);
		}
		if (rect3.leftClicked())
		{
			// 遷移
			changeScene(U"Option", 0.3s);
		}
		if (rect4.leftClicked())
		{
			// ゲーム終了
			System::Exit();
		}
	}

	// 描画関数（オプション）
	void draw() const override
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
private:
	const Font font{ 40 };
	String text = U"";
	String textSelectLang = U"";
	String textOption = U"";
	String textExit = U"";
	int height = 100;
	int height2 = 200;
	int height3 = 300;
	int height4 = 400;
	RectF rectText;
	RectF rect;
	RectF rectText2;
	RectF rect2;
	RectF rectText3;
	RectF rect3;
	RectF rectText4;
	RectF rect4;
};
// オプションシーン
class Option : public App::Scene
{
public:
	// コンストラクタ（必ず実装）
	Option(const InitData& init)
		: IScene{ init }
	{
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

		rectRegionTextBGM = font(textBGM).region();
		rectTextBGM = { (WindowSizeWidth / 2) - (rectRegionTextBGM.w / 2) - 150, height,rectRegionTextBGM.w,60 };
		rectText2 = font(textBackMenu).region();
		rect2 = { (WindowSizeWidth / 2) - (rectText2.w / 2), height2,rectText2.w,60 };
	}

	// 更新関数（オプション）
	void update() override
	{
		if (SimpleGUI::SliderAt(U"{:.2f}"_fmt(bgmValue), bgmValue, 0.0, 10.0, Vec2{ (WindowSizeWidth / 2) + (rectRegionTextBGM.w / 2), height + rectRegionTextBGM.h / 2 }))
		{
			// 音量を設定
			getData().audio.setVolume(bgmValue);
		}

		if (rect2.leftClicked())
		{
			// 遷移
			changeScene(U"Title", 0.3s);
		}
	}

	// 描画関数（オプション）
	void draw() const override
	{
		font(textBGM).draw((WindowSizeWidth / 2) - (rectRegionTextBGM.w / 2) - 150, height, ColorF{ 0.25 });
		rect2.draw(Arg::top = ColorF{ 0.5 }, Arg::bottom = ColorF{ 1.0 });
		font(textBackMenu).draw((WindowSizeWidth / 2) - (rectText2.w / 2), height2, ColorF{ 0.25 });
	}
private:
	const Font font{ 40 };
	String textBGM = U"";
	String textBackMenu = U"";
	int height = 100;
	int height2 = 200;
	RectF rectRegionTextBGM;
	RectF rectTextBGM;
	RectF rectText2;
	RectF rect2;
};
class PlayGame : public App::Scene
{
public:

	// コンストラクタ（必ず実装）
	PlayGame(const InitData& init)
		: IScene{ init }
	{
		mapWidth = textureMap.width();
		mapHeight = textureMap.height();
		playerPos = Vec2(WindowSizeWidth / 2, WindowSizeHeight / 2);
		centerPos = Vec2(WindowSizeWidth / 2, WindowSizeHeight / 2);
		camera = Camera2D{ Vec2{ WindowSizeWidth / 2 - PlayerWidth / 2, WindowSizeHeight / 2 - PlayerHeight / 2}, 1.0 };
	}

	// 更新関数（オプション）
	void update() override
	{
		if (counter > 600)
		{
			counter = 0;
		}
		counter++;
		// 選択肢に対応する確率分布
		DiscreteDistribution distribution(
		{
			30,
			30,
			50,
			50,
		});

		camera.update();
		const auto t = camera.createTransformer();
		const ScopedRenderStates2D sampler{ SamplerState::RepeatLinear };

		// マップを描く | Draw the map
		DrawMap(playerPos, textureMap, font);

		// プレイヤーを描く | Draw the player
		DrawPlayer(texturePlayer, isPlayerFacingRight, playerPos);

		// 弾を描画する
		DrawBullets(bullets);
		// 弾情報を更新する
		UpdateBullets(bullets, Scene::DeltaTime(), playerPos, camera);

		if (counter % 10 == 0 || counter == 0)
		{
			// 敵情報を生成する
			CreateEnemy(enemies, camera, options, distribution);
		}
		// 敵を描画する
		DrawEnemy(textureEnemy, enemies);
		// 敵情報を更新する
		UpdateEnemies(enemies, Scene::DeltaTime(), playerPos);

		CheckPlayerBulletEnemyCollision(bullets, enemies);

		// Aキーが押されていたら | If A key is pressed
		if (KeyA.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPos.x = (playerPos.x - speed * Scene::DeltaTime());
			isPlayerFacingRight = false;
		}

		// Sキーが押されていたら | If S key is pressed
		if (KeyS.pressed())
		{
			// プレイヤーが下に移動する | Player moves bottom
			playerPos.y = (playerPos.y + speed * Scene::DeltaTime());
		}

		// Dキーが押されていたら | If D key is pressed
		if (KeyD.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPos.x = (playerPos.x + speed * Scene::DeltaTime());
			isPlayerFacingRight = true;
		}

		// Wキーが押されていたら | If W key is pressed
		if (KeyW.pressed())
		{
			// プレイヤーが上に移動する | Player moves up
			playerPos.y = (playerPos.y - speed * Scene::DeltaTime());
		}

		camera.jumpTo(playerPos, 1.0);

		// マウスの左ボタンが押されていたら
		if (MouseL.pressed())//downに後でする
		{
			// マウスの位置を取得する | Gets the mouse position
			Vec2 mousePos = Cursor::Pos();

			// マウスの位置に向かって弾を発射する// Fires the bullet towards the mouse position
			FireCreateBullet(playerPos, mousePos, bullets);
		}
	}

	// 描画関数（オプション）
	void draw() const override
	{
	}
private:
	DiscreteDistribution distribution;
	int counter = -1;
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };
	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture texturePlayer{ U"🦖"_emoji };
	const Texture textureEnemy{ U"🦖"_emoji };
	//texturePlayer.resized(PlayerWidth);
	// マップ画像を使用する為のTexture宣言
	const Texture textureMap{ PathImage + U"/map.png", TextureDesc::Mipped };
	// プレイヤーの移動スピード | Player's movement speed
	double speed = 600.0;
	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;
	// プレイヤーの位置
	Vec2 playerPos;
	Vec2 centerPos;
	Array<Bullet> bullets;
	Array<Enemy> enemies;
	Camera2D camera;

	/// @brief 弾の移動と削除を行います。
	/// @param bullets 
	/// @param deltaTime 
	/// @param playerPos 
	/// @param camera 
	void UpdateBullets(Array<Bullet>& bullets, double deltaTime, Vec2 playerPos, const Camera2D& camera)
	{
		for (auto& bullet : bullets)
		{
			bullet.pos += (bullet.direction * bullet.speed * deltaTime);
		}

		//// 画面外の弾を削除
		//bullets.remove_if([playerPos](const Bullet& b)
		//	{
		//		return (not b.getCircle().intersects(Scene::Rect().setPos(playerPos.x, playerPos.y)));
		//	});

		// カメラのビューポートを取得する
		const auto viewportRect = camera.getRegion();

		// ビューポート外の弾を削除する
		bullets.remove_if([&](const Bullet& bullet)
		{
			return !viewportRect.intersects(bullet.getCircle());
		});
	}
	/// @brief 敵情報更新
	/// @param enemies 
	/// @param deltaTime 
	/// @param playerPos 
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
	/// @brief 敵を生成する
	/// @param enemies 
	/// @param camera 
	/// @param options 
	/// @param distribution 
	void CreateEnemy(Array<Enemy>& enemies, const Camera2D& camera, Array<int>& options, DiscreteDistribution& distribution)
	{
		Enemy enemy;
		enemy.HP = 10;
		enemy.speed = 80;
		enemy.height = 50;
		enemy.width = 50;

		// カメラのビューポートを取得する
		const auto viewportRect = camera.getRegion();

		double result = DiscreteSample(options, distribution);

		int x = 0;
		int y = 0;
		if (result == 1)
		{
			//右
			x = Random(viewportRect.x + WindowSizeWidth, viewportRect.x + WindowSizeWidth + 10);
			y = Random(viewportRect.y, viewportRect.y + WindowSizeHeight);
		}
		else if (result == 2)
		{
			//左
			x = Random(viewportRect.x + WindowSizeWidth, viewportRect.x + WindowSizeWidth + 10);
			y = Random(viewportRect.y, viewportRect.y + WindowSizeHeight);
		}
		else if (result == 3)
		{
			//上
			x = Random(viewportRect.x, viewportRect.x + WindowSizeWidth);
			y = Random(viewportRect.y, viewportRect.y - 10);
		}
		else if (result == 4)
		{
			//下
			x = Random(viewportRect.x, viewportRect.x + WindowSizeWidth);
			y = Random(viewportRect.y + WindowSizeHeight, viewportRect.y + WindowSizeHeight + 10);
		}

		enemy.pos = Vec2{ x,y };

		enemies.push_back(enemy);
	}
	/// @brief 弾を生成する
	/// @param playerPos 
	/// @param mousePos 
	/// @param bullets 
	void FireCreateBullet(Vec2 playerPos, Vec2 mousePos, Array<Bullet>& bullets)
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

		//mapTexture(WindowSizeWidth / 2, WindowSizeHeight / 2, mapWidth, mapHeight).draw();
		//mapTexture(WindowSizeWidth/2, WindowSizeHeight/2, mapWidth, mapHeight).draw();
		mapTexture.repeated(256, 256).drawAt(0, 0);
	}
	/// @brief プレイヤーを描画します
	/// @param playerTexture 自機画像
	/// @param isPlayerFacingRight 自機向きのフラグ
	void DrawPlayer(Texture playerTexture, bool isPlayerFacingRight, Vec2 playerPos)
	{
		playerTexture
			.scaled(1)
			.mirrored(isPlayerFacingRight)
			.draw(playerPos.x - PlayerWidth / 2, playerPos.y - PlayerHeight / 2);
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

	// 選択肢
	Array<int> options =
	{
		1,//U"$右",
		2,//U"$左",
		3,//U"$上",
		4//U"$下",
	};

};

// メイン関数 | Main function
void Main()
{
	// ウィンドウのタイトル | Window title
	Window::SetTitle(U"KyoryuFire-Ver0.1");
	// ウィンドウのサイズ | Window size
	Window::Resize(WindowSizeWidth, WindowSizeHeight);
	//// フルスクリーンモードのデフォルトを有効にするか | Whether to enable fullscreen mode by default
	//Window::SetFullscreen(true);
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	// ウィンドウを中心に移動
	Window::Centering();
	//ウィンドウを手動でリサイズできるようにする
	Window::SetStyle(WindowStyle::Sizable);
	//仮想ウィンドウサイズが新しいシーンのサイズになります
	Scene::SetResizeMode(ResizeMode::Virtual);

	// シーンマネージャーを作成
	// ここで GameData が初期化される
	App manager;

	// シーンを登録
	manager.add<SelectLang>(U"SelectLang");
	manager.add<Title>(U"Title");
	manager.add<Option>(U"Option");
	manager.add<PlayGame>(U"PlayGame");

	// "SelectLang" シーンから開始
	manager.init(U"SelectLang");

	// 音声ファイルへのパスを読み込み
	String bgm = PathMusic + U"/PreparationBattle001.wav";
	//String lan = U"";

	// Audio を作成
	manager.get().get()->audio = Audio{ bgm ,Loop::Yes };
	// 再生
	manager.get().get()->audio.play();

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
