#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

class SinhVien {
private:
    string maSV;
    string ten;
    int tuoi;
    float diem;

public:
    SinhVien() : maSV(""), ten(""), tuoi(0), diem(0.0f) {}
    // Nhập dữ liệu
    friend istream& operator>>(istream& is, SinhVien& sv) {
        cout << "Nhập mã sinh viên: ";
        is >> sv.maSV;
        cout << "Nhập tên sinh viên: ";
        is.ignore();
        getline(is, sv.ten);
        cout << "Nhập tuổi: ";
        is >> sv.tuoi;
        cout << "Nhập điểm: ";
        is >> sv.diem;
        return is;
    }

    //Xuất ra màn hình
    friend ostream& operator<<(ostream& os, const SinhVien& sv) {
        os << "Mã SV: " << sv.maSV << ", Tên: " << sv.ten << ", Tuổi: " << sv.tuoi << ", Điểm: " << sv.diem;
        return os;
    }
    friend ifstream& operator>>(ifstream& ifs, SinhVien& sv) {
        ifs >> sv.maSV;
        ifs.ignore();
        getline(ifs, sv.ten);
        ifs >> sv.tuoi;
        ifs >> sv.diem;
        return ifs;
    }

    //Toán tử so sánh theo điểm
    bool operator<(const SinhVien& other) const {
        return diem < other.diem;
    }

    //Lấy mã SV
    string getMaSV() const {
        return maSV;
    }

    // Lấy điểm
    float getDiem() const {
        return diem;
    }

    //Hàm nhập dữ liệu từ file

};

class List_SinhVien {
private:
    list<SinhVien> dsSV;

public:
    void nhapDanhSach(int n) {
        for (int i = 0; i < n; ++i) {
            SinhVien sv;
            cout << "Nhập thông tin sinh viên " << (i + 1) << ":\n";
            cin >> sv;
            dsSV.push_back(sv);
        }
    }

    void xuatDanhSach() {
        for (const auto& sv : dsSV) {
            cout << sv << endl;
        }
    }

    void sapXep() {
        dsSV.sort();
    }

    SinhVien timMax() {
        return *max_element(dsSV.begin(), dsSV.end());
    }

    SinhVien timMin() {
        return *min_element(dsSV.begin(), dsSV.end());
    }
    void xoaSinhVien(const string& maSV) {
        dsSV.remove_if([&](SinhVien& sv) {
            return sv.getMaSV() == maSV;
        });
    }
    void themSinhVien(const SinhVien& sv) {
        dsSV.push_back(sv);
    }
    void docTuFile(const string& tenFile) {
        ifstream ifs(tenFile);
        if (!ifs) {
            cerr << "Không thể mở file: " << tenFile << endl;
            return;
        }

        int soLuong;
        ifs >> soLuong;

        for (int i = 0; i < soLuong; ++i) {
            SinhVien sv;
            ifs >> sv;
            dsSV.push_back(sv);
        }
    }
};

class App {
private:
    List_SinhVien danhSach;
public:
    void menu() {
        int choice;
        do {
            cout << "\nMenu:\n";
            cout << "1. Nhập danh sách sinh viên\n";
            cout << "2. Xuất danh sách sinh viên\n";
            cout << "3. Sắp xếp danh sách sinh viên\n";
            cout << "4. Tìm max điểm\n";
            cout << "5. Tìm min điểm\n";
            cout << "6. Xóa sinh viên\n";
            cout << "7. Thêm sinh viên\n";
            cout << "8. Đọc danh sách từ file\n";
            cout << "0. Thoát\n";
            cout << "Chọn: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int n;
                    cout << "Nhập số lượng sinh viên: ";
                    cin >> n;
                    danhSach.nhapDanhSach(n);
                    break;
                }
                case 2:
                    danhSach.xuatDanhSach();
                    break;
                case 3:
                    danhSach.sapXep();
                    cout << "Đã sắp xếp danh sách.\n";
                    break;
                case 4: {
                    SinhVien maxSV = danhSach.timMax();
                    cout << "Sinh viên có điểm max: " << maxSV << endl;
                    break;
                }
                case 5: {
                    SinhVien minSV = danhSach.timMin();
                    cout << "Sinh viên có điểm min: " << minSV << endl;
                    break;
                }
                case 6: {
                    string maSV;
                    cout << "Nhập mã sinh viên cần xóa: ";
                    cin >> maSV;
                    danhSach.xoaSinhVien(maSV);
                    cout << "Đã xóa sinh viên có mã: " << maSV << endl;
                    break;
                }
                case 7: {
                    SinhVien sv;
                    cin >> sv;
                    danhSach.themSinhVien(sv);
                    cout << "Đã thêm sinh viên.\n";
                    break;
                }
                case 8: {
                    string tenFile;
                    cout << "Nhập tên file: ";
                    cin >> tenFile;
                    danhSach.docTuFile(tenFile);
                    cout << "Đã đọc danh sách từ file.\n";
                    break;
                }
                case 0:
                    cout << "Thoát chương trình.\n";
                    break;
                default:
                    cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    App app;
    app.menu();
    return 0;
}
