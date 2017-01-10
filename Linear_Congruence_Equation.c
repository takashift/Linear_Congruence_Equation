#include <stdio.h>

int calc_gcd(int m, int n)
{
    int change;
    
    if (m < n){
        change = n;
        n=m;
        m=change;
    }
    
    int r = m % n;
    while (r != 0){
        m = n;
        n = r;
        r = m % n;
    }
    
    return n;
}

int Euclidean(int arg_m, int arg_n)
{
    int change;
    int m[100];
    m[1] = arg_m;
    int n[100];
    n[1] = arg_n;
    int l[100];
    
    if (m[1] < n[1]){
        change = n[1];
        n[1]=m[1];
        m[1]=change;
    }
    
    int i = 0;
    int r = m[1] % n[1];
    
    printf("ユークリッドアルゴリズムより\n");
    
    do {
        i++;
        l[i] = m[i]/n[i];
        printf("%d = %d * %d + ", m[i], n[i], l[i]);
        m[i+1] = n[i];
        n[i+1] = r;
        r = m[i+1] % n[i+1];
        printf("%d・・・(%d)\n", n[i+1], i);
    } while (r != 0);
    
    int imax = i;
    
    while (i>0) {
        printf("(%d)より\n", i);
        printf("  %d = %d - %d * %d・・・(%d)'\n", n[i+1], m[i], n[i], l[i], i);
        i--;
    }
    
    int j = imax+1;
    int a[100];
    int b[100];
    int x[100];
    int y[100];
    
    if (imax == 1){
        a[j] = m[imax];
        x[j] = 1;
        b[j] = n[imax];
        y[j] = l[imax]*(-1);
        printf("  %d = %d * (%d) + %d * (%d)・・・(%d)\n", n[imax+1], a[j], x[j], b[j], y[j], j);
    }
    else {
        i = imax-1;
        printf("(%d)'を(%d)'に代入\n", imax-1, imax);
        a[j] = n[i];
        x[j] = l[i] * l[imax] + 1;
        b[j] = m[i];
        y[j] = l[imax]*(-1);
        printf("  %d = %d * (%d) + %d * (%d)・・・(%d)\n", n[imax+1], a[j], x[j], b[j], y[j], j);
    }
    
    while (i > 1) {
        i--;
        printf("(%d)'を(%d)に代入\n", i, j);
        j++;
        if (n[i+1] == a[j-1]) {
            x[j] = x[j-1];
            y[j] = l[i]*(-1) * x[j-1] + y[j-1];
            a[j] = m[i];
            b[j] = n[i];
        }
        else if(n[i+1] == b[j-1]) {
            x[j] = l[i]*(-1) * y[j-1] + x[j-1];
            y[j] = y[j-1];
            a[j] = n[i];
            b[j] = m[i];
        }
        printf("  %d = %d * (%d) + %d * (%d)・・・(%d)\n", n[imax+1], a[j], x[j], b[j], y[j], j);
    }
    
    if(a[j] > b[j])
        return y[j];
    
    else
        return x[j];
}

void pya(int a, int b, int mod, int gcd){
    int k;
    int x;
    int z;
    
    x = Euclidean(a, mod);
    printf("より%dx ≡ 1(mod %d)の解は x ≡ %d(mod %d)", a, mod, x, mod);
    while(x < 0) {
        x += mod;
        printf(" = %d(mod %d)", x, mod);
    }
    printf("\n");
    
    for (k = 0; k <= 100; k++){
        z = ((mod * k) + b) % a;
        x = ((mod * k) + b) / a;
        if (z == 0){
            break;
        }
    }
    
    printf("よって%dx ≡ %d(mod %d)の解は ", a*gcd, b*gcd, mod*gcd);
    // ｂが１のときの解をb倍して、modより大きければ小さくなるまでmodを引く
    printf("x ≡");
    printf(" %d", x);
    for(int i=1; i<gcd; i++){
        x = x + mod;
        printf(", %d", x);
    }
    
    printf("(mod %d)\n", mod);
    
    printf("\n");
    printf("k = %d\n", k);
}

int main(){
    int ax;
    int b;
    int mod;
    int gcd;
    int change;
    
    while (1) {
        printf("(終了時はax:0)\n数値ax:");
        scanf("%d", &ax);
        
        if(ax==0)
            break;
        
        printf("数値b:");
        scanf("%d", &b);
        printf("mod:");
        scanf("%d", &mod);
        
        printf("\n");
        
        while (b < 0) {
            b = b + mod;
            printf(" ≡ %d(mod %d)\n", b, mod);
        }
        
        gcd = calc_gcd(ax, mod);
        
        printf("G.C.D.(%d, %d) = %d\n", ax, mod, gcd);
        
        if(gcd == 1)
            printf("よって唯一解を持つ\n");
        
        if (b % gcd != 0){
            printf("%dは%dを割り切れないため解はなし\n", gcd, b);
        }
        
        else if(gcd == 1) {
            pya(ax, b, mod, gcd);
        }
        
        else if(gcd >= 2){
            pya(ax/gcd, b/gcd, mod/gcd, gcd);
        }
        
        printf("\n");
    }
    
    return 0;
}
