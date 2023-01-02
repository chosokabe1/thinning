// longest.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

int main(void) {
    Mat img = imread("C:\\ex\\sen\\thinning\\skeleton2\\003_002.bmp", 0);
    if (img.empty()) return -1;
    Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);
    Mat checked = Mat::zeros(img.rows, img.cols, CV_8U);
    vector<int> start(2);
    vector<int> next(2);
    vector<vector<int> > next_candidate;
    vector<vector<int>> intersection;
    vector<vector<int>> yet_check_rout;

    bool finished = false;
    int x, y, i, j;
    for (y = 0; y < img.rows; y++) {
        for (x = 0; x < img.cols; x++) {
            if (img.at<uchar>(y,x) == 255) {
                finished = true;
                start[0] = y;
                start[1] = x;
                checked.at<uchar>(y,x) = 255;
                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        // ８近傍にuncheckedな画素値があれば
                        if (img.at<uchar>(y + j, x + i) == 255 && checked.at<uchar>(y + j, x + i) == 0) {
                            vector<int> next_candidate_temp(2);
                            next_candidate_temp[0] = y + j;
                            next_candidate_temp[1] = x + i;
                            next_candidate.push_back(next_candidate_temp);
                            // checkedにする
                            checked.at<uchar>(y + j, x + i) = 255;
                        }
                    }
                }
                if (next_candidate.size() == 1) {
                    vector<int> intersection_temp(2);
                    intersection_temp[0] = y;
                    intersection_temp[1] = x;
                    intersection.push_back(intersection_temp);
                    next[0] = next_candidate.back()[0];
                    next[1] = next_candidate.back()[1];
                }
                else {
                    if (next_candidate.size() > 1) {
                        next[0] = next_candidate.back()[0];
                        next[1] = next_candidate.back()[1];
                        next_candidate.pop_back();
                        while (next_candidate.size()) {
                            vector<int> yet_check_rout_temp(2);
                            yet_check_rout_temp[0] = next_candidate.back()[0];
                            yet_check_rout_temp[1] = next_candidate.back()[1];
                            yet_check_rout.push_back(yet_check_rout_temp);
                            next_candidate.pop_back();
                        }
                    }
                }
                break;
            }
        }
        if (finished) {
            break;
        }
    }
    cout << "start:(" << start[0] << "," << start[1] << ")" << endl;
    bool search_finished = false;
    while (!search_finished) {
        y = next[0];
        x = next[1];
        //next_candidateを見つけるループ
        finished = false;
        for (int j = -1; j <= 1; j++) {
            for (int i = -1; i <= 1; i++) {
                // ８近傍にuncheckedな画素値があれば
                if (img.at<uchar>(y + j, x + i) == 255 && checked.at<uchar>(y + j, x + i) == 0 ){
                    vector<int> next_candidate_temp(2);
                    next_candidate_temp[0] = y + j;
                    next_candidate_temp[1] = x + i;
                    next_candidate.push_back(next_candidate_temp);
                    // checkedにする
                    checked.at<uchar>(y + j, x + i) = 255;
                }
            }
        }
        // next_candidateがなければyet_check_routを思い出す
        if (next_candidate.size() == 0) {
            vector<int> intersection_temp(2);
            intersection_temp[0] = y;
            intersection_temp[1] = x;
            intersection.push_back(intersection_temp);
            // さらにyet_check_routがなければ終わる
            if (yet_check_rout.size() == 0) {
                search_finished = true;
                continue;
            }
            next[0] = yet_check_rout.back()[0];
            next[1] = yet_check_rout.back()[1];
            yet_check_rout.pop_back();
            continue;
        }
        else {
            // 候補点が複数あれば交点とする
            if (next_candidate.size() > 1) {
                vector<int> intersection_temp(2);
                intersection_temp[0] = y;
                intersection_temp[1] = x;
                intersection.push_back(intersection_temp);
            }
            // 次の座標を決める
            next[0] = next_candidate.back()[0];
            next[1] = next_candidate.back()[1];
            next_candidate.pop_back();
            // それ以外の座標をyet_check_routとする
            while (next_candidate.size()) {
                vector<int> yet_check_rout_temp(2);
                yet_check_rout_temp[0] = next_candidate.back()[0];
                yet_check_rout_temp[1] = next_candidate.back()[1];
                yet_check_rout.push_back(yet_check_rout_temp);
                next_candidate.pop_back();
            }
        }
    }

    imwrite("C:\\ex\\sen\\thinning\\checked.bmp", checked);


    for (y = 0; y < img.rows; y++) {
        for (x = 0; x < img.cols; x++) {
            if (img.at<uchar>(y, x) == 255) {
                dst.at<Vec3b>(y, x)[0] = 255;
                dst.at<Vec3b>(y, x)[1] = 255;
                dst.at<Vec3b>(y, x)[2] = 255;
            }
        }
    }
    for (i = 0; i < intersection.size(); i++) {
        y = intersection[i][0];
        x = intersection[i][1];
        circle(dst, Point(x,y), 3, Scalar(255, 0, 0), -1);
    }

    imwrite("C:\\ex\\sen\\thinning\\dst.bmp", dst);

    //ここまでできた



    for (i = 0; i < intersection.size(); i++) {
        next[0] = intersection[i][0];
        next[1] = intersection[i][1];
        bool search_finished = false;
        while (!search_finished) {
            y = next[0];
            x = next[1];
            //next_candidateを見つけるループ
            finished = false;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    // ８近傍にuncheckedな画素値があれば
                    if (img.at<uchar>(y + j, x + i) == 255) {
                        vector<int> next_candidate_temp(2);
                        next_candidate_temp[0] = y + j;
                        next_candidate_temp[1] = x + i;
                        next_candidate.push_back(next_candidate_temp);
                    }
                }
            }
            // next_candidateがなければyet_check_routを思い出す
            if (next_candidate.size() == 0) {
                vector<int> intersection_temp(2);
                intersection_temp[0] = y;
                intersection_temp[1] = x;
                intersection.push_back(intersection_temp);
                // さらにyet_check_routがなければ終わる
                if (yet_check_rout.size() == 0) {
                    search_finished = true;
                    continue;
                }
                next[0] = yet_check_rout.back()[0];
                next[1] = yet_check_rout.back()[1];
                yet_check_rout.pop_back();
                continue;
            }
            else {
                // 次の座標を決める
                next[0] = next_candidate.back()[0];
                next[1] = next_candidate.back()[1];
                next_candidate.pop_back();
                // それ以外の座標をyet_check_routとする
                while (next_candidate.size()) {
                    vector<int> yet_check_rout_temp(2);
                    yet_check_rout_temp[0] = next_candidate.back()[0];
                    yet_check_rout_temp[1] = next_candidate.back()[1];
                    yet_check_rout.push_back(yet_check_rout_temp);
                    next_candidate.pop_back();
                }
            }
        }
    }
    while (intersection.size()) {
        cout << "intersection" << "(" << intersection.back()[0] << "," << intersection.back()[1] << ')' << endl;
        intersection.pop_back();
    }
    return 0;
}
