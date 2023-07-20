#include "Fish.h"
#include"Player.h"
#include"DxLib.h"

// コンストラクタ
Fish::Fish(float _x)
{
	imagecnt = -1;
	WeitTime = 0;
	flg = false;

	x = _x;
	y = 400;
	w = WIDTH;
	h = HEIGHT;

	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);

	
}

Fish::~Fish()
{

}

void Fish::Update()
{
	if (++WeitTime % 11 == 0 && flg ==true) {
		imagecnt = imagecnt+1;
	}
	if (imagecnt >= 5) {
		imagecnt = 0;
	}

	imageX = x + (w / 2);
	imageY = y + (h / 2);


	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	

}

void Fish::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	DrawRotaGraph(imageX, imageY, 1.0f, 0, image[imagecnt], true);
	DrawBox(150, 400, 500, 480, 0x00ff00, 0);
}

bool Fish::GetFlg() {
	return flg;
}

void Fish::LoadImage()
{
	/*第一引数はファイル名を指定します。
		第二引数は画像の分割総数を指定します。今回ならば１２個なので１２を指定します。
		第三、第四引数は横と縦向きに対する画像の分割数です。
		今回であれば、横は３列、縦は４行になっているので、３と４を指定します。
		第５、第６引数は分割画像一つ分の大きさを指定します。
		第７引数は、分割された画像一つ一つのグラフィックハンドルを保存するint型の配列へのポインタを指定します。
		今回は１２個分読むので、int image[12]などという配列を作り、そのポインタを渡します。
		配列の中には以下のようにグラフィックハンドルが格納されます。数字は配列の添字を表しています。*/

	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);
}

