#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
void print_info(const cv::Mat& mat)
{
    using namespace std;

    // �v�f�̌^�ƃ`�����l�����̑g�ݍ��킹�B
    // ���ʂ̓s���ɂ��A�T���v���Ŏg�p����l�̂݋L�q
    cout << "type: " << (
        mat.type() == CV_8UC3 ? "CV_8UC3" :
        mat.type() == CV_16SC1 ? "CV_16SC1" :
        mat.type() == CV_64FC2 ? "CV_64FC2" :
        "other"
        ) << endl;

    // �v�f�̌^
    cout << "depth: " << (
        mat.depth() == CV_8U ? "CV_8U" :
        mat.depth() == CV_16S ? "CV_16S" :
        mat.depth() == CV_64F ? "CV_64F" :
        "other"
        ) << endl;

    // �`�����l����
    cout << "channels: " << mat.channels() << endl;

    // �o�C�g�񂪘A�����Ă��邩
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

// �v���O�����̎��s: Ctrl + F5 �܂��� [�f�o�b�O] > [�f�o�b�O�Ȃ��ŊJ�n] ���j���[
// �v���O�����̃f�o�b�O: F5 �܂��� [�f�o�b�O] > [�f�o�b�O�̊J�n] ���j���[

// ��Ƃ��J�n���邽�߂̃q���g: 
//    1. �\�����[�V���� �G�N�X�v���[���[ �E�B���h�E���g�p���ăt�@�C����ǉ�/�Ǘ����܂� 
//   2. �`�[�� �G�N�X�v���[���[ �E�B���h�E���g�p���ă\�[�X�Ǘ��ɐڑ����܂�
//   3. �o�̓E�B���h�E���g�p���āA�r���h�o�͂Ƃ��̑��̃��b�Z�[�W��\�����܂�
//   4. �G���[�ꗗ�E�B���h�E���g�p���ăG���[��\�����܂�
//   5. [�v���W�F�N�g] > [�V�������ڂ̒ǉ�] �ƈړ����ĐV�����R�[�h �t�@�C�����쐬���邩�A[�v���W�F�N�g] > [�����̍��ڂ̒ǉ�] �ƈړ����Ċ����̃R�[�h �t�@�C�����v���W�F�N�g�ɒǉ����܂�
//   6. ��قǂ��̃v���W�F�N�g���ĂъJ���ꍇ�A[�t�@�C��] > [�J��] > [�v���W�F�N�g] �ƈړ����� .sln �t�@�C����I�����܂�
