class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int up = 0;
        int down = matrix.size()-1;
        int left = 0;
        int right = matrix[0].size()-1;
        vector<int>res;
        int d = 0;
        while(up <= down && right >= left){
        if(d == 0 ){
        for(int i = left ; i <= right ;i++ ){
            res.push_back(matrix[up][i]);
        }
        up ++;
        }
        if(d==1){
         for(int i = up ; i <= down ;i++ ){
            res.push_back(matrix[i][right]);
        }
        right--;
        }
        if(d == 2){
         for(int i = right ; i >= left ;i-- ){
            res.push_back(matrix[down][i]);
        }
        down--;
        }
        if(d == 3){
        for(int i = down ; i >= up ;i-- ){
            res.push_back(matrix[i][left]);
        }
        left++;
        }
            d = (d+1) % 4;
        }
        return res;
    }
};
