#include "rsa.h"


//求最大公约数
BigInt get_gcd(BigInt num1, BigInt num2) {
	BigInt mod, gcd;
	char end = '0';
	if(num1.digit<num2.digit||(num1.digit==num2.digit && (num1.num, num2.num)<0)) {
		BigInt temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
#ifdef __DEBUG__
//	printf("num1:%s\n", num1.num);
//	printf("num2:%s\n", num2.num);
#endif
	mod = BigIntMod(num1, num2);

#ifdef __DEBUG__
//	printf("mod:%s\t%d\n", mod.num, mod.digit);
//	printf("--------%d\n", mod.num[0] == end);
#endif
	if(mod.num[0] == end) {
		printf("%s\n", num2.num);
		return num2;
	} else {
		return get_gcd(num2, mod);
	}
	
	
}

//快速幂模算法 
BigInt exp_mod(BigInt num1, BigInt num2, BigInt mode){
	BigInt sum, rst_mod, rst_div, fixNum;
//	BigInt rst_mod_pointer, rst_div_pointer;
	
	strcpy(fixNum.num, "2");
	fixNum.digit = 1;
	fixNum.sign = '1';

	strcpy(sum.num, "1");
	sum.digit = 1;
	sum.sign = '1';
	
	num1 = BigIntMod(num1, mode);
	
	while(num2.num[0] != '0'){
		rst_mod = BigIntMod(num2, fixNum);
		if(rst_mod.num[0] == '1'){
			BigInt rst_mul;
			rst_mul = BigIntMul(sum, num1);
			sum = BigIntMod(rst_mul, mode);
		}
		num2 = BigIntDiv(num2, fixNum);
		BigInt midData;
		midData = BigIntMul(num1, num1);
		num1 = BigIntMod(midData, mode);
	}
	
	return sum;
} 

//扩展欧几里得算法
BigInt exEuclid(BigInt num1, BigInt num2){
	BigInt result;
	BigInt x1, x2, x3, y1, y2, y3;
	
	
} 

//判断是否为素数(未实现)
bool detect_prime(BigInt oddNum) {
	char data[MAX];
	int length;

	strcpy(data, oddNum.num);//data即为要判断的数
	length = oddNum.digit;

	return true;
}

//生成随机的素数(只实现了生成随机的奇数)
BigInt generatePrime() {
	BigInt midNum,fixNum;

	//fixNUM为累加数，值保持为2
	strcpy(fixNum.num, "2");
	fixNum.digit = 1;
	fixNum.sign = '1';

	//生成一个随机的奇数
	for(int i = 0; i < PRIME_DIGIT; i++) {
		if(i == 0) {
			int r = rand()%10+1;
			midNum.num[i] = r+'0';
		} else {
			int r = rand()%10;
			midNum.num[i] = r+'0';
		}
	}
	midNum.num[PRIME_DIGIT] = '\0';
	if((midNum.num[PRIME_DIGIT-1]-'0')%2 == 0) {
		midNum.num[PRIME_DIGIT-1] = midNum.num[PRIME_DIGIT-1]+1;
	}
	midNum.digit = strlen(midNum.num);
	midNum.sign = '1';

	//由生成的奇数产生一个素数(先不忙实现素数)
//	while(!detect_prime(midNum)) {
//		BigInt* rst;
//		rst = (BigInt*)malloc(sizeof(BigInt));
//
//		rst = BigIntAdd(midNum, fixNum);
//		strcpy(midNum.num,rst.num);
//		midNum.digit = rst.digit;
//		midNum.sign = rst.sign;
//	}

	return midNum;
}

//密钥生成函数实现
void generate_keys(publicKey* pub_key, privateKey* pri_key) {
	BigInt p,p_1, q,q_1, midNum, e, d;//p，q为选择的素数，midNum为中间值
	BigInt gcd, phi_n;
	
	BigInt n;
	FILE *fp;
#ifdef _WRITE	
	if((fp = fopen("primeNum.txt", "w")) == NULL){
		printf("文件打开错误！");
		exit(1);
	}
#endif
	p.sign = '1';
	q.sign = '1';
	
	//此素数由网上素数生成器生成 
	char prim_num_p[51] = "27409488245517115276142322168576189279543123341141";
	char prim_num_q[51] = "84277931986502860248650900613893446066184963788813";
	strcpy(p.num, "27409488245517115276142322168576189279543123341141");
	strcpy(q.num, "84277931986502860248650900613893446066184963788813");
	p.digit = strlen(p.num);
	q.digit = strlen(q.num);
	
	//生成一个随机的素数
//	p = generatePrime();
//	q = generatePrime();
#ifdef _WRITE
	fputs(p.num, fp);
	fputc('\n',fp);
	fputs(q.num, fp);
//	fclose(fp);
//	printf("%s\t%c\t%d\n", p.num,p.sign,p.digit);
//	printf("%s\t%c\t%d\n", q.num,q.sign,q.digit);
#endif
	n = BigIntMul(p, q);

	strcpy(pub_key->modulus.num, n.num);
	pub_key->modulus.digit = n.digit;
	pub_key->modulus.sign = n.sign;

	strcpy(pri_key->modulus.num, n.num);
	pri_key->modulus.digit = n.digit;
	pri_key->modulus.sign = n.sign;

	pri_key->prime_p = p;
	pri_key->prime_q = q;


#ifdef __DEBUG__
//	printf("n:%s\n", n.num);
	printf("pub_key.modulus:%s\n", pub_key->modulus.num);
	printf("pri_key.modulus:%s\n", pri_key->modulus.num);
	printf("pri_key.prime_p:%s\n", pri_key->prime_p.num);
	printf("pri_key.prime_q:%s\n", pri_key->prime_q.num);
//	gcd = get_gcd(p, q);
//	printf("gcd:%s\n", gcd.num);
#endif

	BigInt fixNum;
	strcpy(fixNum.num, "1");
	fixNum.digit = 1;
	fixNum.sign = '1';
	
	p_1 = BigIntSub(p, fixNum);
	q_1 = BigIntSub(q, fixNum);
	printf("p-1:%s\n", p_1.num);
	printf("q-1:%s\n", q_1.num);
	phi_n = BigIntMul(p_1, q_1);
#ifdef _WRITE
	fputc('\n', fp);
	fputs(phi_n.num, fp);
#endif
#ifdef __DEBUG__
	printf("phi_n:%s\t%c\t%d\n", phi_n.num, phi_n.sign, phi_n.digit);
#endif
	
	strcpy(e.num, "17");
	e.digit = strlen(e.num);
	e.sign = '1';
#ifdef __DEBUG__
//	gcd = get_gcd(e,phi_n);
//	printf("gcd:%s\t%c\t%d\n", gcd.num, gcd.sign, gcd.digit);
#endif

	strcpy(pub_key->public_exp.num, e.num);
	pub_key->public_exp.digit = e.digit;
	pub_key->public_exp.sign = e.sign;
	pri_key->public_exp = pub_key->public_exp;
	
#ifdef __DEBUG__
//	printf("pub_key.public_exp:%s\t%c\t%d\n", pub_key->public_exp.num, pub_key->public_exp.sign, pub_key->public_exp.digit);
//	printf("pri_key.public_exp:%s\t%c\t%d\n", pri_key->public_exp.num, pri_key->public_exp.sign, pri_key->public_exp.digit);
#endif

	BigInt phi_n_2;
	BigInt mid;
	
	strcpy(mid.num, "2");
	mid.digit = strlen(mid.num);
	mid.sign = '1';
	
	phi_n_2 = BigIntSub(phi_n, mid);
	
#ifdef __DEBUG__
	printf("phi_n_2:%s\n", phi_n_2.num);
#endif
	
	d = exp_mod(e, phi_n_2, phi_n);
	
#ifdef __DEBUG__
	printf("d:%s\t%d\n", d.num, d.digit);
#endif

	BigInt test, test_mul;
	test_mul = BigIntMul(e, d);
	printf("e=%s\nd=%s\ne*d=%s\t%d\n", e.num,d.num ,test_mul.num, test_mul.digit);
#ifdef _WRITE
	fputc('\n', fp);
	fputs(test_mul.num, fp);
	fclose(fp);
#endif
	test = BigIntMod(test_mul, phi_n);
	printf("test:%s\t%d\n", test.num,test.digit);
}

//加密函数实现
BigInt* encrypt(char* cipher, char* message, int length, publicKey kpub);

//解密函数实现
BigInt* decrypt(char* message ,char *cipher, int length, privateKey kpri);
