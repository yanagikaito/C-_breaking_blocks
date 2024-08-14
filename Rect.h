#pragma once

// 長方形の構造体の定義
struct Rect {

    // ブロック定義
    int Block[BLOCK_NUM_X][BLOCK_NUM_Y];

    int x, y, w, h;

    // ０か1かボールが存在するかしないか
    bool flag;
};
