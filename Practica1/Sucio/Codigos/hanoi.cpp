void hanoi(int M, int i, int j){
    if(M > 0){
        hanoi(M-1, i, 6-i-j);
        cout << i << " -> " << j << endl;
        hanoi(M-1, 6-i-j, j);
    }
}