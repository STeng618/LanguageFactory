#include <value/cellReference.hpp>

#define MAX_EXCEL_COL (1 << 14)
#define EXCEL_UNDERFINED 0

using namespace Langfact;

std::unique_ptr<CellReference> CellReference::create(std::string_view expr) {
    std::array<int, 4> points {EXCEL_UNDERFINED, EXCEL_UNDERFINED, EXCEL_UNDERFINED, EXCEL_UNDERFINED}; // l, t, r, b
    bool is_second_part = false;
    short part_idx = 0;
    for (char c: expr) {
        if (c == '$') continue; 
        if (c == ':') {
            if (is_second_part) return nullptr;
            is_second_part = true;
            part_idx = 0;
            continue;
        }
        if (c >= 'A' && c <= 'Z') {
            if (part_idx == 1) return nullptr;
            points[is_second_part * 2] = points[is_second_part * 2] * 26 + (c - 'A' + 1);
            if (points[is_second_part * 2] > MAX_EXCEL_COL) return nullptr;
            continue;
        }
        if (c >= '0' && c <= '9') {
            part_idx = 1;
            if (points[is_second_part * 2 + 1] == 0 && c == '0') return nullptr; 
            points[is_second_part * 2 + 1] = points[is_second_part * 2 + 1] * 10 + (c - '0');
            continue;
        }
        return nullptr;
    }
    bool are_cols_fully_defined = points[0] && points[2];
    bool are_cols_fully_undefined = !points[0] && !points[2];
    bool are_rows_fully_defined = points[1] && points[3];
    bool are_rows_fully_undefined = !points[1] && !points[3];
    bool are_cols_awkward = !are_cols_fully_defined && !are_cols_fully_undefined;
    bool are_rows_awkward = !are_rows_fully_defined && !are_rows_fully_undefined;

    bool has_errors = (
        (!is_second_part && (!points[0] || !points[1])) 
        || (is_second_part && (are_cols_awkward || are_rows_awkward)) 
        || (are_cols_fully_defined && points[2] < points[0])
        || (are_rows_fully_defined && points[3] < points[1])
    );

    if (has_errors) return nullptr;
    if (!is_second_part) {
        points[2] = points[0];
        points[3] = points[1];
    }
    return std::unique_ptr<CellReference>(new CellReference(expr, points[0], points[1], points[2], points[3]));
}
