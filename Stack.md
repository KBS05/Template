## Stack

- [Stack](#stack)
  - [Infix  to postfix](#Infix_To_Postfix)
  - [Infix  to prefix](#Infix_To_Prefix)
  - [Postfix  to prefix](#Postfix_To_Prefix)
  - [Postfix  to Infix](#Postfix_To_Infix)
  - [Prefix  to postfix](#Prefix_To_Postfix)
  - [Prefix  to Infix](#Prefix_To_Infix)
  - [Stack using 2 Queue](#Stack_using_2_Queue)
  - [Stack using 1 Queue](#Stack_using_1_Queue)
  - [Queue using 2 Stack](#Queue_using_2_Stack)

## Infix_To_Postfix
```C++
    string infixToPostfix(string s)
    {
        // Your code here
        stack<char>st;
        string res = "";
        st.push('(');
        s += ')';
        auto prec = [](char ch){
            if(ch=='+'||ch=='-')    return 1;
            else if(ch=='*'||ch=='/')   return 2;
            else if(ch=='^')    return 3;
            return 0;
        };
        for(char ch : s){
            if(ch=='('){
                st.push(ch);
            }
            else if(ch==')'){
                while(!st.empty() && st.top()!='('){
                    res.push_back(st.top());
                    st.pop();
                }
                st.pop();
            }
            else if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||(ch>='0'&&ch<='9')){
                res.push_back(ch);
            }
            else{
                while(!st.empty() && prec(st.top())>=prec(ch)){
                    res.push_back(st.top());
                    st.pop();
                }
                st.push(ch);
            }
        }
        return res;
    }

```

## Infix_To_Prefix

```C++
string infixToPrefix(string s) {
	int l = s.size();
	reverse(s.begin(), s.end());
	for (int i=0;i<l;i++) {
		if (s[i] == '(') {
			s[i] = ')';
		}
		else if (s[i] == ')') {
			s[i] = '(';
		}
	}
	string res = infixToPostfix(s);
	reverse(res.begin(), res.end());
	return res;
}
```

## Postfix_to_Prefix
```C++
string postToPre(string s){
    stack<string> st;
    int length = s.size();
    for (int i = 0; i < length; i++) {
        char ch = s[i];
        if ((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')) {
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            string temp = s[i] + op2 + op1;
            st.push(temp);
        }
        else {
            st.push(string(1, s[i]));
        }
    }
    string ans = "";
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }
    return ans;
}
```

## Postfix_To_Infix
```C++
string Postfix_to_Infix(string s)
{
    stack<string> st;
    for (int i=0; s[i]!='\0'; i++){
        if (isOperand(s[i])){
           string op(1, s[i]);
           st.push(op);
        }
        else{
            string op1 = st.top();
            st.pop();
            string op2 = st.top();
            st.pop();
            st.push("(" + op2 + s[i] + op1 + ")");
        }
    }
    return st.top();
}
```

## Prefix_To_Postfix
```C++
string preToPost(string pre_exp){
	stack<string> s;
	int length = pre_exp.size();
	for (int i = length - 1; i >= 0; i--)
	{
	    char ch = pre_exp[i];
	    if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')){
	        string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			string temp = op1 + op2 + pre_exp[i];
			s.push(temp);
	    }
		else {
			s.push(string(1,ch));
		}
	}
	return s.top();
}
```

## Prefix_To_Infix
```C++
string preToInfix(string s) {
    stack<string>st;
    int length = s.size();
    for (int i = length - 1; i >= 0; i--) {
        if (isOperator(s[i])) {
            string op1 = st.top();   st.pop();
            string op2 = st.top();   st.pop();
            string temp = "(" + op1 + s[i] + op2 + ")";
            st.push(temp);
        }
        else {
            st.push(string(1, s[i]));
        }
    }
    return st.top();
}
```
## Stack_using_2_Queue
```C++
// Push -> O(1)  and Pop and Top -> O(n)
class MyStack {
    queue<int>q1,q2;
public:
    MyStack() {
        while(!q1.empty())  q1.pop();
        while(!q2.empty())  q2.pop();
    }
    
    void push(int x) {
        q1.push(x);
    }
    
    int pop() {
        int s = q1.size();
	// first remove size-1 element the remaining element will be the top element of stack
        for(int i=0;i<s-1;i++){
            q2.push(q1.front());
            q1.pop();
        }
        int val = q1.front();
        q1.pop();
	// At this point q1 will be empty, now vacant q2 (all element from q2 to q1)
        while(!q2.empty()){
            q1.push(q2.front());
            q2.pop();
        }
        return val;
    }
    
    int top() {
        int s = q1.size();
        for(int i=0;i<s-1;i++){
            q2.push(q1.front());
            q1.pop();
        }
        int val = q1.front();
        q2.push(val);
        q1.pop();
        while(!q2.empty()){
            q1.push(q2.front());
            q2.pop();
        }
        return val;
    }
    
    bool empty() {
        return (q1.size()==0);
    }
};


// Push -> O(n)  and Pop and Top -> O(1)
class MyStack {
    queue<int>q1,q2;
public:
    MyStack() {
        while(!q1.empty())  q1.pop();
        while(!q2.empty())  q2.pop();
    }
    
    void push(int x) {
        // first vacant q1
        while(!q1.empty()){
            q2.push(q1.front());
            q1.pop();
        }
        // push x to q1 and the all element from q2 to q1
        q1.push(x);
        while(!q2.empty()){
            q1.push(q2.front());
            q2.pop();
        }
    }
    
    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return (q1.size()==0);
    }
};


```


## Stack_using_1_Queue
```C++
class MyStack {
    queue<int>q1;
public:
    MyStack() {
        while(!q1.empty())  q1.pop();
    }
    
    void push(int x) {
        int s = q1.size();
        q1.push(x);
        for(int i=0;i<s;i++){
            q1.push(q1.front());
            q1.pop();
        }
    }
    
    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }
    
    int top() {
        return q1.front();
    }
    
    bool empty() {
        return (q1.size()==0);
    }
};
```

## Queue_using_2_Stack
```C++
class MyQueue {
    stack<int>s1,s2;
public:
    MyQueue() {
        while(!s1.empty())  s1.pop();
        while(!s2.empty())  s2.pop();
    }
    
    void push(int x) {
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(x);
        while(!s2.empty()){
            s1.push(s2.top());
            s2.pop();
        }
    }
    
    int pop() {
        int val = s1.top();
        s1.pop();
        return val;
    }
    
    int peek() {
        return s1.top();
    }
    
    bool empty() {
        return (s1.size()==0);
    }
};

```
