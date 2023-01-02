#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
void print_info(const cv::Mat& mat)
{
    using namespace std;

    // 要素の型とチャンネル数の組み合わせ。
    // 紙面の都合により、サンプルで使用する値のみ記述
    cout << "type: " << (
        mat.type() == CV_8UC3 ? "CV_8UC3" :
        mat.type() == CV_16SC1 ? "CV_16SC1" :
        mat.type() == CV_64FC2 ? "CV_64FC2" :
        "other"
        ) << endl;

    // 要素の型
    cout << "depth: " << (
        mat.depth() == CV_8U ? "CV_8U" :
        mat.depth() == CV_16S ? "CV_16S" :
        mat.depth() == CV_64F ? "CV_64F" :
        "other"
        ) << endl;

    // チャンネル数
    cout << "channels: " << mat.channels() << endl;

    // バイト列が連続しているか
    cout << "continuous: " <<
        (mat.isContinuous() ? "true" : "false") << endl;
}
int main(void) {
    int m, n;
    cout << "col:"; cin >> m;
    cout << "row:"; cin >> n;

    vector<vector<int> > x(m, vector<int>(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "x[" << i << "][" << j << "] = " << x[i][j] << '\n';
         }
    }

    cout << x.back()[0] << x.back()[1] << endl;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << "x[" << i << "][" << j << "] = " << x[i][j] << '\n';
        }
    }
    x.pop_back();
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n; j++) {
            cout << "x[" << i << "][" << j << "] = " << x[i][j] << '\n';
        }
    }
    return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
