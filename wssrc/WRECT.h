#ifndef WRECT_H
#define WRECT_H
struct WRECT : RECT {
    void operator+=(RECT* r) {
        this->left += r->left;
        this->top += r->top;
        this->bottom += r->top;
        this->right += r->left;
    }
    void operator+=(RECT r) {
        this->left += r.left;
        this->top += r.top;
        this->bottom += r.top;
        this->right += r.left;
    }
    void operator*=(RECT* r) {
        this->left += r->left;
        this->top += r->top;
        this->bottom += r->bottom;
        this->right += r->right;
    }
    void operator=(RECT* r) {
        this->left = r->left;
        this->top = r->top;
        this->bottom = r->bottom;
        this->right = r->right;
    }
    void operator-=(RECT r) {
        this->left-= r.left;
        this->top-= r.top;
        this->right-= r.right;
        this->bottom-= r.bottom;
    }
};
#endif