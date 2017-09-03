//category : d&c

#include <stdio.h>
#include <math.h>
// pts[][0]:x��ǥ, pts[][1]:y��ǥ
int pts[100000][2];		//�Է� ������ �迭
int temp[100000][2];	//merge sort�� �ӽ� �迭
int min(int a, int b){
	if (a < b) return a;
	return b;
}
// (x1,y1), (x2,y2)�� �Ÿ� ����
int sqdist(int x1, int y1, int x2, int y2){
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}
// if(xy==0) -> x�࿡ ���� ����
// if(xy==1) -> y�࿡ ���� ����
void merge(int s, int m, int e, int xy){
	int ix1 = s;
	int ix2 = m;

	for (int i = s; i < e; i++){
		if (ix1 == m){
			temp[i][0] = pts[ix2][0];
			temp[i][1] = pts[ix2][1];
			ix2++;
		}
		else if (ix2 == e){
			temp[i][0] = pts[ix1][0];
			temp[i][1] = pts[ix1][1];
			ix1++;
		}
		else if (pts[ix1][xy] > pts[ix2][xy]){
			temp[i][0] = pts[ix2][0];
			temp[i][1] = pts[ix2][1];
			ix2++;
		}
		else{
			temp[i][0] = pts[ix1][0];
			temp[i][1] = pts[ix1][1];
			ix1++;
		}
	}
	for (int i = s; i < e; i++){
		pts[i][0] = temp[i][0];
		pts[i][1] = temp[i][1];
	}
}
void mergesort(int s, int e, int xy){
	if (e - s <= 1)		//����ó��
		return;
	int m = (s + e) / 2;
	mergesort(s, m, xy);
	mergesort(m, e, xy);
	merge(s, m, e, xy);
}
//[s,e)
int band(int s, int e, int delta){
	int m = (s + e) / 2;
	//cent_x,cent_y : ����
	int cent_x = pts[m][0];
	int cent_y = pts[m][1];
	int from, to;
	int i, j;

	//������������ delta���� ���� ���� Ž��(left)
	for (from = m; from >= s; from--){
		if (pts[from][0] < cent_x - delta)
			break;
	}
	//from�� �������� �����ϹǷ�, +1
	from++;
	//������������ delta���� ���� ���� Ž��(right)
	for (to = m; to < e; to++){
		if (pts[to][0] > cent_x + delta)
			break;
	}
	//y�� ����
	mergesort(from, to, 1);
	int dist = 900000000;		//�ʱ�ȭ�� MAX���� ����
	for (i = from; i < to; i++){
		for (j = i - 15; j < i + 15; j++){
			if (i == j)		//�Ȱ��� �������� �Ÿ��� ��� ������
				continue;
			if (j < from || j >= to)	//���� ��Ż ���� ó��
				continue;
			dist = min(dist, sqdist(pts[i][0], pts[i][1], pts[j][0], pts[j][1]));
		}
	}
	//���� �ܰ踦 ���� �ٽ� x�� ����
	mergesort(from, to, 0);
	return dist;
}
//[s,e)
//�ִ� �Ÿ��� ��ȯ��
int closest_pair(int s, int e){
	int sqdelta;
	if (e - s < 4){		//���� 2�� �̰ų� 3���� ����� ����ó��
		sqdelta = sqdist(pts[s][0], pts[s][1], pts[s + 1][0], pts[s + 1][1]);
		if (e - s == 3){	//���� 3���� ����� ����ó��
			sqdelta = min(sqdelta, sqdist(pts[s + 2][0], pts[s + 2][1], pts[s + 1][0], pts[s + 1][1]));
			sqdelta = min(sqdelta, sqdist(pts[s + 2][0], pts[s + 2][1], pts[s][0], pts[s][1]));
		}
		return sqdelta;
	}
	int m = (s + e) / 2;

	sqdelta = min(closest_pair(s, m), closest_pair(m, e));
	//sqdelta�� �Ÿ� �����̹Ƿ� ��Ʈ���� �� band�Լ� ȣ��
	//+1�� float->int ĳ������ ���� ó���� ���� ���ս� ����
	sqdelta = min(sqdelta, band(s, e, sqrt((float)sqdelta) + 1));
	return sqdelta;
}
int main(){
	int i;
	int n;
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		scanf("%d%d", &pts[i][0], &pts[i][1]);
	}
	//x�� ����
	mergesort(0, n, 0);
	printf("%d", closest_pair(0, n));
	return 0;
}

