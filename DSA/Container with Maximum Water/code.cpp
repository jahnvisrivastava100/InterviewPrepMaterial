class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int maxm = -1;
        int j = n-1;
        int i = 0;
        int s = 0;
        //brute force O(N2)
        // for(int i = 0 ; i < n; i++){
        //     for(int j = i+1 ; j < n ; j++){
        //        s = min(height[i], height[j])* (j-i);
        //        cout<<s;
        //        maxm = max(maxm ,s);
        //     }
        // }
        // return maxm;

        //optimised appraoch
        while( i < j){
  
          //the only benifit we will get is in shrinking window in the direction where  the    container is minimum becuase ultimately the area in which we will have water is equal to min of 2 only
         s = 0; 
         s = min(height[i],height[j])*(j-i);
         maxm = max(maxm ,s);
         if(height[i] < height[j]) i++;
         else j--;


        }
   return maxm;

    }
};
