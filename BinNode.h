#pragma once

#include <algorithm>
#include <memory>

using std::max;
using std::min;
using std::swap;


#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ

template <typename T> struct BinNode { //�������ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
	T data; //��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; //���ڵ㼰���Һ���
	int height; //�߶ȣ�ͨ�ã�
	int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������
 // ���캯��
	BinNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) { }
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
	// �����ӿ�
	int size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNodePosi(T) insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T) succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	BinNodePosi(T) pred(); //�Լ�������յ�ֱ��ǰ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
 // �Ƚ������е�����������һ���������в��䣩
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
	bool operator== (BinNode const& bn) { return data == bn.data; } //����
	/*DSA*/
	/*DSA*/BinNodePosi(T) zig(); //˳ʱ����ת
	/*DSA*/BinNodePosi(T) zag(); //��ʱ����ת
};

/*DSA*/#define HeightUpdated(x) /*�߶ȸ��³�������*/ \
/*DSA*/        ( (x).height == 1 + max( stature( (x).lc ), stature( (x).rc ) ) )
#define Balanced(x) ( stature( (x).lc ) == stature( (x).rc ) ) //����ƽ������
#define BalFac(x) ( stature( (x).lc ) - stature( (x).rc ) ) //ƽ������
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) ) //AVLƽ������


/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )

 /******************************************************************************************
  * ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
  ******************************************************************************************/
#define sibling(p) /*�ֵ�*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )

#define uncle(x) /*����*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )

#define FromParentTo(x) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);
} //��e��Ϊ��ǰ�ڵ�����Ӳ��������

template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);
} //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������

template <typename T> int BinNode<T>::size() //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
{ 
	int s = 1; //���뱾��
	if (lc) s += lc->size(); //�ݹ������������ģ
	if (rc) s += rc->size(); //�ݹ������������ģ
	return s;
}

template <typename T> void stretchByZag(BinNodePosi(T) & x) {
	/*DSA*/   int c = 0; //��¼��ת����
	int h = 0;
	BinNodePosi(T) p = x; while (p->rc) p = p->rc; //���ڵ㣬�����������յĸ�
	while (x->lc) x = x->lc; x->height = h++; //ת����ʼ�����ͨ·��ĩ��
	for (; x != p; x = x->parent, x->height = h++) { //��x�������ѿգ�������һ��
		while (x->rc) //���򣬷�����
			/*DSA*/ {
			x->zag(); //��xΪ����zag��ת
			/*DSA*/c++;
			/*DSA*/
		}
	} //ֱ���ִ������ĸ�
	/*DSA*/printf("\nh = %d, c = %d\n\n", h, c);
}

//ͨ��zig��ת������������x��������Ҳ�ͨ·
template <typename T> void stretchByZig(BinNodePosi(T) & x, int h) {
	/*DSA*/   int c = 0;
	for (BinNodePosi(T) v = x; v; v = v->rc) {
		while (v->lc)
			/*DSA*/ {
			v = v->zig();
			/*DSA*/c++;
			/*DSA*/
		}
		v->height = --h;
	}
	while (x->parent) x = x->parent;
	/*DSA*/printf("\nh = %d, c = %d\n\n", h, c);
}

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //��λ�ڵ�v��ֱ�Ӻ��
	BinNodePosi(T) s = this; //��¼��̵���ʱ����
	if (rc) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
		s = rc; //��������
		while (HasLChild(*s)) s = s->lc; //�����С���Ľڵ�
	}
	else //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
	{ 
		while (IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}

template <typename T>
BinNode<T>* BinNode<T>::pred()
{
	BinNodePosi(T) s = this; //��¼ǰ������ʷ����
	if (lc) //����������ӣ���ǰ����������
	{
		s = lc;
		while (HasRChild(*s)) s = s->rc;
	}
	else if (IsRChild(*s)) //���������������ǰ�����丸�ڵ�
	{
		s = s->parent;
	}
	else //�����ӣ���û��������
	{
		while (IsLChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}


template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit) { //��������������㷨ͳһ���
	//switch (rand() % 5) { //�˴������ѡ���������ԣ�������ѡ��
	//case 1: travIn_I1(this, visit); break; //������#1
	//case 2: travIn_I2(this, visit); break; //������#2
	//case 3: travIn_I3(this, visit); break; //������#3
	//case 4: travIn_I4(this, visit); break; //������#4
	//default: travIn_R(this, visit); break; //�ݹ��
	//}
	travIn_R(this, visit);
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_R(BinNodePosi(T) x, VST& visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

//�˴�ʡ����һ��travlevel�㷨����Ϊ����Ҫ���в�α���

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travPost(VST& visit) { //��������������㷨ͳһ���
	//switch (rand() % 2) { //�˴������ѡ���������ԣ�������ѡ��
	//case 1: travPost_I(this, visit); break; //������
	//default: travPost_R(this, visit); break; //�ݹ��
	//}
	travPost_R(this, visit);
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPost_R(BinNodePosi(T) x, VST& visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travPre(VST& visit) { //��������������㷨ͳһ���
	//switch (rand() % 3) { //�˴������ѡ���������ԣ�������ѡ��
	//case 1: travPre_I1(this, visit); break; //������#1
	//case 2: travPre_I2(this, visit); break; //������#2
	//default: travPre_R(this, visit); break; //�ݹ��
	//}
	travPre_R(this, visit);
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_R(BinNodePosi(T) x, VST& visit) { //��������������㷨���ݹ�棩
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

template <typename T> BinNodePosi(T) BinNode<T>::zag() 
{
	BinNodePosi(T) rChild = rc;
	rChild->parent = this->parent;
	if (rChild->parent)
		((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
	rc = rChild->lc; if (rc) rc->parent = this;
	rChild->lc = this; this->parent = rChild;
	return rChild;
}

template <typename T> BinNodePosi(T) BinNode<T>::zig() 
{
	BinNodePosi(T) lChild = lc;
	lChild->parent = this->parent;
	if (lChild->parent)
		((this == lChild->parent->rc) ? lChild->parent->rc : lChild->parent->lc) = lChild;
	lc = lChild->rc; if (lc) lc->parent = this;
	lChild->rc = this; this->parent = lChild;
	return lChild;
}