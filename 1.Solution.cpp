//907子数组的最小值之和
//使用了贡献法加单调栈
class Solution {
public:
    const int modd = 1e9 + 7;
    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        arr.emplace_back(-1);
        stack<int> st;
        st.emplace(-1);
        long long sum = 0; 
        for(int i = 0; i <= n; i++){
            while(st.size() > 1 && arr[st.top()] >= arr[i]){
                int kk = st.top();
                st.pop();
                long long arr1 = static_cast<long long>(arr[kk]);
                sum += arr1 * (kk - st.top()) * (i - kk);  
                sum %= modd;
            }
            st.emplace(i);
        }
        return sum;
    }
};


//2104子数组范围和
//使用了贡献法加单调栈
class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
       int n = nums.size();
       nums.emplace_back(-INT_MAX);
       stack<int>st;
       st.emplace(-1);
       long long sum = 0;
       for(int i = 0; i <= n; i++){
           while(st.size() > 1 && nums[st.top()] >= nums[i]){
               int kk = st.top();
               cout << kk << ' ';
               st.pop();
               long long arr1 = static_cast<long long> (nums[kk]);
               sum += arr1 * (kk - st.top())* (i - kk); 
           }
           st.emplace(i);
       }
       cout << sum << ' ';
       nums.erase(nums.end() - 1);
       nums.emplace_back(INT_MAX);
       stack<int>st1;
       st1.emplace(-1);
       long long sum_max = 0;
       for(int i = 0; i <= n; i++){
           while(st1.size() > 1 && nums[st1.top()] <= nums[i]){
               int kk = st1.top();
               st1.pop();
               long long arr1 = static_cast<long long >(nums[kk]);
               sum_max += arr1 * (kk - st1.top()) * (i - kk);
           }
           st1.emplace(i);
       }
       return abs(sum - sum_max);
    }
};



//1856子数组最小乘积的最大值
//使用贡献法加单调栈
class Solution {
public:
    const int modd = 1e9 + 7;
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();
        vector<long long>front_sum(n+1,0);
        for(int i = 1; i <= n; i++){
            front_sum[i] = front_sum[i - 1] + nums[i-1];
        }
        
        nums.emplace_back(-1);
        stack<int> st;
        st.emplace(-1);
        long long he = 0;
        long long max = 0;
        for(int i = 0; i <= n; i++){
            while(st.size() > 1 && nums[st.top()] >= nums[i]){
                int kk = st.top();
                st.pop();
                long long sum = front_sum[i] - front_sum[st.top() + 1];
                long long arr1 =static_cast<long long>(nums[kk]);
                he  = arr1 * sum;
                max = max > he? max : he;
            }
            st.emplace(i);
        }
        max %= modd;
        return max;
    }
};



//1106解析布尔表达式
//栈模拟
class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;
        for(auto temp : expression){
            vector<char> store;
            if(temp != ')'){
                st.emplace(temp);
            }
            else{
                while(st.top() != '('){
                    char get = st.top();
                    store.emplace_back(get);
                    st.pop();
                }
                st.pop();
                char operator1 = st.top();
                st.pop();
                if(operator1 == '|' ){
                    st.emplace(find(store.begin(),store.end(),'t') != store.end()?'t':'f');
                } 
                if(operator1 == '&' ){
                    st.emplace(find(store.begin(),store.end(),'f')!= store.end()?'f':'t');
                } 
                if(operator1 == '!' ){
                    st.emplace(store[0] == 't'?'f':'t');
                } 
            }
        }
        return st.top() == 't'?true:false;
    }
};



//剑指Offer_51数组中的逆序对
//归并排序的使用
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        sum = 0;
        vector<int> tmp(nums);
        merge(0,nums.size()-1,nums,tmp);
        //for_each(nums.begin(),nums.end(),[](int x){cout << x << ' ';});
        return sum;
    }
    void merge(int left, int right, vector<int>& nums, vector<int> & tmp){
        if(left >= right)return;
        int mid = (left + right)/2;
        merge(left,mid,nums,tmp);
        merge(mid + 1,right,nums,tmp);
        int curl = left, curr = mid + 1;        
        int cnt = left;
        //cout << left << ' '<< right << ' '<<endl;
        while(curl <= mid && curr <= right){
            if(nums[curl] > nums[curr]){
                if(nums[curl] > nums[curr])
                    sum += mid - curl + 1;
                // if(nums[curl] == nums[curr])
                //     sum += mid - curl;
                tmp[cnt++] = nums[curr++];
            }
            else{
                tmp[cnt++] = nums[curl++];
            }
        }
        while(curl <= mid){
            tmp[cnt++] = nums[curl++];
        }
        while(curr <= right){
            tmp[cnt++] = nums[curr++];
        }
        for(int i = left; i <= right; i++){
            nums[i] = tmp[i];
        }
        //for_each(nums.begin(),nums.end(),[](int x){cout << x << ' ';});
    }
private:
    int sum;
};



//1两数之和
//unordered_map哈希map的使用，记录了四种哈希map插入元素的方式，用operator[]的方式比较快
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       unordered_map<int,int> store;
       vector<int>get;
       for(int i = 0; i < nums.size(); i++){
           int sub = target - nums[i];
           unordered_map<int,int>::iterator it = store.find(sub);
           if(it != store.end() && it->second != i){
               get.emplace_back(i);
               get.emplace_back(it->second);
               return get;
           }
           //four method of insert element of unordered_map 
           //store.emplace(nums[i],i);//method1
           //store.insert(make_pair(nums[i],i));//method2
           //store.insert(pair<int,int>(nums[i],i));//method3
           store[nums[i]] = i;
       } 
       return get;
    }
};


//两数相加
//使用了队列来简化逻辑
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * input = new ListNode;
        int carry = 0;
        queue<int> stl1;
        queue<int> stl2;
        queue<int> st3;
        ListNode *cur1 = l1, *cur2 = l2;
        while(cur1 != NULL){
            stl1.emplace(cur1->val);
            cur1 = cur1->next;
        }
        while(cur2 != NULL){
            stl2.emplace(cur2->val);
            cur2 = cur2->next;
        }
        while(!stl1.empty() && !stl2.empty()){
            int data = stl1.front() + stl2.front() + carry;
            stl1.pop();
            stl2.pop();
            carry = data >= 10?1:0;
            st3.emplace(data % 10);
        }
        while(!stl1.empty()){
            int data = stl1.front() + carry;
            stl1.pop();
            carry = data >= 10?1:0;
            st3.emplace(data % 10);
        }
        while(!stl2.empty()){
            int data = stl2.front() + carry;
            stl2.pop();
            carry = data >= 10?1:0;
            st3.emplace(data % 10);
        }

        //cout << st3.size();
        ListNode *inputtemp = input;
        inputtemp->val = st3.front();
        st3.pop();
        while(!st3.empty()){
            ListNode *newdata = new ListNode(st3.front());
            cout << st3.front()<< ' ';
            st3.pop();
            //cout << input->val << ' ';
            inputtemp->next = newdata;
            inputtemp = inputtemp->next;
        }
        if(carry == 1){
            ListNode *newdata = new ListNode(1);
            inputtemp->next = newdata;
        }
        return input;
    }
};