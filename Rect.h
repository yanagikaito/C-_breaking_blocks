#pragma once

// �����`�̍\���̂̒�`
struct Rect {

    // �u���b�N��`
    int Block[BLOCK_NUM_X][BLOCK_NUM_Y];

    int x, y, w, h;

    // �O��1���{�[�������݂��邩���Ȃ���
    bool flag;
};
