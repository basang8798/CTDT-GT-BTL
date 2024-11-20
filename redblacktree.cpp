#include <iostream>
using namespace std;

enum Mau
{
    DO,
    DEN
};

struct Nut
{
    int gia_tri;
    Mau mau;
    Nut *cha;
    Nut *trai;
    Nut *phai;
};

class CayDoDen
{
private:
    Nut *goc;
    Nut *nutNIL;

    void suaLaiThem(Nut *nutMoi)
    {
        Nut *ongNoi;
        while (nutMoi != goc && nutMoi->cha->mau == DO)
        {
            if (nutMoi->cha == nutMoi->cha->cha->trai)
            {
                ongNoi = nutMoi->cha->cha->phai;
                if (ongNoi->mau == DO)
                {
                    nutMoi->cha->mau = DEN;
                    ongNoi->mau = DEN;
                    nutMoi->cha->cha->mau = DO;
                    nutMoi = nutMoi->cha->cha;
                }
                else
                {
                    if (nutMoi == nutMoi->cha->phai)
                    {
                        nutMoi = nutMoi->cha;
                        xoayTrai(nutMoi);
                    }
                    nutMoi->cha->mau = DEN;
                    nutMoi->cha->cha->mau = DO;
                    xoayPhai(nutMoi->cha->cha);
                }
            }
            else
            {
                ongNoi = nutMoi->cha->cha->trai;
                if (ongNoi->mau == DO)
                {
                    nutMoi->cha->mau = DEN;
                    ongNoi->mau = DEN;
                    nutMoi->cha->cha->mau = DO;
                    nutMoi = nutMoi->cha->cha;
                }
                else
                {
                    if (nutMoi == nutMoi->cha->trai)
                    {
                        nutMoi = nutMoi->cha;
                        xoayPhai(nutMoi);
                    }
                    nutMoi->cha->mau = DEN;
                    nutMoi->cha->cha->mau = DO;
                    xoayTrai(nutMoi->cha->cha);
                }
            }
        }
        goc->mau = DEN;
    }

    void xoayTrai(Nut *x)
    {
        Nut *y = x->phai;
        x->phai = y->trai;
        if (y->trai != nutNIL)
        {
            y->trai->cha = x;
        }
        y->cha = x->cha;
        if (x->cha == nullptr)
        {
            goc = y;
        }
        else if (x == x->cha->trai)
        {
            x->cha->trai = y;
        }
        else
        {
            x->cha->phai = y;
        }
        y->trai = x;
        x->cha = y;
    }

    void xoayPhai(Nut *x)
    {
        Nut *y = x->trai;
        x->trai = y->phai;
        if (y->phai != nutNIL)
        {
            y->phai->cha = x;
        }
        y->cha = x->cha;
        if (x->cha == nullptr)
        {
            goc = y;
        }
        else if (x == x->cha->phai)
        {
            x->cha->phai = y;
        }
        else
        {
            x->cha->trai = y;
        }
        y->phai = x;
        x->cha = y;
    }

    void suaLaiXoa(Nut *nut)
    {
        while (nut != goc && nut->mau == DEN)
        {
            if (nut == nut->cha->trai)
            {
                Nut *anhEm = nut->cha->phai;
                if (anhEm->mau == DO)
                {
                    anhEm->mau = DEN;
                    nut->cha->mau = DO;
                    xoayTrai(nut->cha);
                    anhEm = nut->cha->phai;
                }
                if (anhEm->trai->mau == DEN && anhEm->phai->mau == DEN)
                {
                    anhEm->mau = DO;
                    nut = nut->cha;
                }
                else
                {
                    if (anhEm->phai->mau == DEN)
                    {
                        anhEm->trai->mau = DEN;
                        anhEm->mau = DO;
                        xoayPhai(anhEm);
                        anhEm = nut->cha->phai;
                    }
                    anhEm->mau = nut->cha->mau;
                    nut->cha->mau = DEN;
                    anhEm->phai->mau = DEN;
                    xoayTrai(nut->cha);
                    nut = goc;
                }
            }
            else
            {
                Nut *anhEm = nut->cha->trai;
                if (anhEm->mau == DO)
                {
                    anhEm->mau = DEN;
                    nut->cha->mau = DO;
                    xoayPhai(nut->cha);
                    anhEm = nut->cha->trai;
                }
                if (anhEm->trai->mau == DEN && anhEm->phai->mau == DEN)
                {
                    anhEm->mau = DO;
                    nut = nut->cha;
                }
                else
                {
                    if (anhEm->trai->mau == DEN)
                    {
                        anhEm->phai->mau = DEN;
                        anhEm->mau = DO;
                        xoayTrai(anhEm);
                        anhEm = nut->cha->trai;
                    }
                    anhEm->mau = nut->cha->mau;
                    nut->cha->mau = DEN;
                    anhEm->trai->mau = DEN;
                    xoayPhai(nut->cha);
                    nut = goc;
                }
            }
        }
        nut->mau = DEN;
    }

    void thayThe(Nut *cu, Nut *moi)
    {
        if (cu->cha == nullptr)
        {
            goc = moi;
        }
        else if (cu == cu->cha->trai)
        {
            cu->cha->trai = moi;
        }
        else
        {
            cu->cha->phai = moi;
        }
        moi->cha = cu->cha;
    }

    Nut *timMin(Nut *nut)
    {
        while (nut->trai != nutNIL)
        {
            nut = nut->trai;
        }
        return nut;
    }

public:
    CayDoDen()
    {
        nutNIL = new Nut{0, DEN, nullptr, nullptr, nullptr};
        nutNIL->trai = nutNIL;
        nutNIL->phai = nutNIL;
        goc = nutNIL;
    }

    void them(int gia_tri)
    {
        Nut *nutMoi = new Nut{gia_tri, DO, nullptr, nutNIL, nutNIL};
        Nut *cha = nullptr;
        Nut *hienTai = goc;

        while (hienTai != nutNIL)
        {
            cha = hienTai;
            if (nutMoi->gia_tri < hienTai->gia_tri)
            {
                hienTai = hienTai->trai;
            }
            else
            {
                hienTai = hienTai->phai;
            }
        }

        nutMoi->cha = cha;
        if (cha == nullptr)
        {
            goc = nutMoi;
        }
        else if (nutMoi->gia_tri < cha->gia_tri)
        {
            cha->trai = nutMoi;
        }
        else
        {
            cha->phai = nutMoi;
        }

        if (nutMoi->cha == nullptr)
        {
            nutMoi->mau = DEN;
            return;
        }

        if (nutMoi->cha->cha == nullptr)
        {
            return;
        }

        suaLaiThem(nutMoi);
    }

    void inOrder(Nut *nut)
    {
        if (nut != nutNIL)
        {
            inOrder(nut->trai);
            cout << nut->gia_tri << " ";
            inOrder(nut->phai);
        }
    }

    void hienThi()
    {
        if (goc == nutNIL)
        {
            cout << "Cay rong." << endl;
            return;
        }
        inOrder(goc);
        cout << endl;
    }

    void xoa(int gia_tri)
    {
        Nut *nutCanXoa = goc;
        Nut *x, *y;

        // Tìm nút cần xóa
        while (nutCanXoa != nutNIL && nutCanXoa->gia_tri != gia_tri)
        {
            if (gia_tri < nutCanXoa->gia_tri)
            {
                nutCanXoa = nutCanXoa->trai;
            }
            else
            {
                nutCanXoa = nutCanXoa->phai;
            }
        }

        if (nutCanXoa == nutNIL)
        {
            cout << "Gia tri khong ton tai trong cay!" << endl;
            return;
        }

        y = nutCanXoa;
        Mau mauGocBanDau = y->mau;

        if (nutCanXoa->trai == nutNIL)
        {
            x = nutCanXoa->phai;
            thayThe(nutCanXoa, nutCanXoa->phai);
        }
        else if (nutCanXoa->phai == nutNIL)
        {
            x = nutCanXoa->trai;
            thayThe(nutCanXoa, nutCanXoa->trai);
        }
        else
        {
            y = timMin(nutCanXoa->phai);
            mauGocBanDau = y->mau;
            x = y->phai;
            if (y->cha == nutCanXoa)
            {
                x->cha = y;
            }
            else
            {
                thayThe(y, y->phai);
                y->phai = nutCanXoa->phai;
                y->phai->cha = y;
            }
            thayThe(nutCanXoa, y);
            y->trai = nutCanXoa->trai;
            y->trai->cha = y;
            y->mau = nutCanXoa->mau;
        }

        delete nutCanXoa;

        if (mauGocBanDau == DEN)
        {
            suaLaiXoa(x);
        }
    }

    Nut *timKiem(int gia_tri)
    {
        Nut *hienTai = goc; // Bắt đầu tìm kiếm từ gốc cây
        while (hienTai != nutNIL && hienTai->gia_tri != gia_tri)
        {
            if (gia_tri < hienTai->gia_tri)
            {
                hienTai = hienTai->trai; // Chuyển sang nhánh trái nếu giá trị nhỏ hơn
            }
            else
            {
                hienTai = hienTai->phai; // Chuyển sang nhánh phải nếu giá trị lớn hơn
            }
        }
        return hienTai; // Trả về nút tìm thấy hoặc nút `nutNIL` nếu không tìm thấy
    }

    void timVaHienThi(int gia_tri)
    {
        Nut *ketQua = timKiem(gia_tri);
        if (ketQua == nutNIL)
        {
            cout << "Gia tri " << gia_tri << " khong ton tai trong cay." << endl;
        }
        else
        {
            cout << "Tim thay gia tri " << gia_tri << " trong cay." << endl;
        }
    }
};

int main()
{
    CayDoDen cay;
    cay.them(36);
    cay.them(75);
    cay.them(63);
    cay.them(30);
    cay.them(12);
    cay.them(51);
    cay.them(54);
    cay.them(41);
    cay.them(20);
    cay.them(24);
    cay.them(15);
    cay.them(70);
    cay.them(48);

    cout << "Cay do-den sau khi them cac nut: ";
    cay.hienThi();

    cout << "cay xau khi xoa nut: ";
    cay.xoa(20);
    cay.xoa(51);

    cout << "Cay do-den sau khi xoa cac nut: ";
    cay.hienThi();

    cout << "Tim kiem gia tri 15: ";
    cay.timVaHienThi(1);

    cout << "Tim kiem gia tri 100: ";
    cay.timVaHienThi(0);

    return 0;
}