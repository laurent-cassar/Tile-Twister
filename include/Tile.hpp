#ifndef TILE_HPP
#define TILE_HPP

class Tile {
public:
    Tile();
    Tile(int value, int row, int col);
    
    int getValue() const { return value_; }
    void setValue(int value) { value_ = value; }
    
    int getRow() const { return row_; }
    void setRow(int row) { row_ = row; }
    
    int getCol() const { return col_; }
    void setCol(int col) { col_ = col; }
    
    bool isEmpty() const { return value_ == 0; }
    bool canMergeWith(const Tile& other) const;
    
    void merge(const Tile& other);
    
private:
    int value_;
    int row_;
    int col_;
};

#endif // TILE_HPP