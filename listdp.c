// HOLY LOVENIA - 13515113


/* File : listdp.c */
/* ADT List dengan Double Pointer */
/* Representasi berkait dengan address adalah pointer */
/* infotype adalah integer */


#include "listdp.h"
#include <stdio.h>
#include <stdlib.h>


/* PROTOTYPE */

/****************** TEST LIST KOSONG ******************/

boolean IsEmpty (List L)
{
	return ((First(L) == Nil) && (Last(L) == Nil));
}
/* Mengirim true jika list kosong. Lihat definisi di atas. */


/****************** PEMBUATAN LIST KOSONG ******************/

void CreateEmpty (List *L)
{
	First(*L) = Nil;
	Last(*L) = Nil;
}
/* I.S. L sembarang  */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */


/****************** Manajemen Memori ******************/

address Alokasi (infotype X)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		P = (address) malloc (sizeof (ElmtList));
		if (P != Nil)
		{
			Info(P) = X;
			Next(P) = Nil;
			Prev(P) = Nil;
		}
		return (P);
}
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil. */
/* Misalnya: menghasilkan P, maka Info(P)=X, Next(P)=Nil, Prev(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil. */

void Dealokasi (address P)
{
	Next(P) = Nil;
	Prev(P) = Nil;
	free(P);
}
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */


/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/

address Search (List L, infotype X)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		P = First(L);
		while ((P != Nil) && (Info(P) != X))
		{
			P = Next(P);
		}
		return(P);
}
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */


/****************** PRIMITIF BERDASARKAN NILAI ******************/

/*** PENAMBAHAN ELEMEN ***/

void InsVFirst (List *L, infotype X)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		P = Alokasi(X);
		InsertFirst(L, P);
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void InsVLast (List *L, infotype X)
{
	// KAMUS
	address Last;
	
		// ALGORITMA
		if (IsEmpty(*L))
		{
			InsVFirst(L, X);
		}
		else
		{
			Last = Alokasi(X);
			InsertLast(L, Last);
		}
}
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */


/*** PENGHAPUSAN ELEMEN ***/

void DelVFirst (List *L, infotype *X)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		DelFirst(L, &P);
		*X = Info(P);
		Dealokasi(P);
}
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */

void DelVLast (List *L, infotype *X)
{
	// KAMUS
	address Last;
	
		// ALGORITMA
		*X = Info(Last(*L));
		DelLast(L, &Last);
		Dealokasi(Last);
}
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/

/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/

void InsertFirst (List *L, address P)
{
	// KAMUS
	
	
		// ALGORITMA
		if (IsEmpty(*L))
		{
			First(*L) = P;
			Last(*L) = P;
		}
		else
		{
			Prev(First(*L)) = P;
			Next(P) = First(*L);
			First(*L) = P;
		}
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */

void InsertLast (List *L, address P)
{
	// KAMUS

	
		// ALGORITMA
		if (IsEmpty(*L))
		{
			InsertFirst(L, P);
		}
		else
		{
			Next(Last(*L)) = P;
			Prev(P) = Last(*L);
			Last(*L) = P;
			Next(Last(*L)) = Nil;
		}
}
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void InsertAfter (List *L, address P, address Prec)
{
	// KAMUS

	
		// ALGORITMA
		if (Prec == Last(*L))
		{
			InsertLast(L, P);
		}
		else
		{
			Prev(Next(Prec)) = P;
			Next(P) = Next(Prec);
			Next(Prec) = P;
			Prev(P) = Prec;
		}
}
/* I.S. Prec pastilah elemen list{} P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void InsertBefore (List *L, address P, address Succ)
{
	// KAMUS

	
		// ALGORITMA
		if (Succ == First(*L))
		{
			InsertFirst(L, P);
		}
		else
		{
			Prev(P) = Prev(Succ);
			Next(Prev(Succ)) = P;
			Prev(Succ) = P;
			Next(P) = Succ;
		}
}
/* I.S. Succ pastilah elemen list{} P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sebelum elemen beralamat Succ */


/*** PENGHAPUSAN SEBUAH ELEMEN ***/

void DelFirst (List *L, address *P)
{
	// KAMUS
	
	
		// ALGORITMA
		*P = First(*L);
		if (Next(*P) != Nil)
		{
			First(*L) = Next(*P);
			Prev(First(*L)) = Nil;
			Next(*P) = Nil;
		}
		else
		{
			CreateEmpty(L);
		}
}
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */

void DelLast (List *L, address *P)
{
	// KAMUS
	
	
		// ALGORITMA
		*P = Last(*L);
		if (Prev(*P) == Nil)
		{
			CreateEmpty(L);
		}
		else
		{
			Last(*L) = Prev(*P);
			Next(Last(*L)) = Nil;
			Next(*P) = Nil;
			Prev(*P) = Nil;
		}
}
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, jika ada */

void DelP (List *L, infotype X)
{
	// KAMUS
	address P, Prec;
	
		// ALGORITMA
		
		P = Search(*L, X);
		if (P != Nil)
		{
			if (First(*L) == P)
			{
				DelVFirst(L, &X);
			}
			else
			{
				Prec = Prev(P);
				DelAfter(L, &P, Prec);
			}
		}
}
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* maka P dihapus dari list dan didealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void DelAfter (List *L, address *Pdel, address Prec)
{
	// KAMUS
	
	
		// ALGORITMA
		if (Last(*L) == Next(Prec))
		{
			DelLast(L, Pdel);
		}
		else
		{
			*Pdel = Next(Prec);
			Next(Prec) = Next(*Pdel);
			Prev(Next(Prec)) = Prec;
		}
		Next(*Pdel) = Nil;
		Prev(*Pdel) = Nil;
}
/* I.S. List tidak kosong. Prec adalah anggota list. */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

void DelBefore (List *L, address *Pdel, address Succ)
{
	// KAMUS
	
	
		// ALGORITMA
		if (First(*L) == Prev(Succ))
		{
			DelFirst(L, Pdel);
		}
		else
		{
			*Pdel = Prev(Succ);
			Prev(Succ) = Prev(*Pdel);
			Next(Prev(Succ)) = Succ;
		}
		Next(*Pdel) = Nil;
		Prev(*Pdel) = Nil;
}
/* I.S. List tidak kosong. Succ adalah anggota list. */
/* F.S. Menghapus Prev(Succ): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintForward (List L)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		if (IsEmpty(L))
		{
			printf("[]");
		}
		else
		{
			printf("[");
			P = First(L);
			while (Next(P) != Nil)
			{
				printf("%d,", Info(P));
				P = Next(P);
			}
			printf("%d]", Info(P));
		}
}
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen pertama */
/* ke elemen terakhir secara horizontal ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */

void PrintBackward (List L)
{
	// KAMUS
	address P;
	
		// ALGORITMA
		if (IsEmpty(L))
		{
			printf("[]");
		}
		else
		{
			printf("[");
			P = Last(L);
			while (Prev(P) != Nil)
			{
				printf("%d,", Info(P));
				P = Prev(P);
			}
			printf("%d]", Info(P));
		}
}
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, isi list dicetak dari elemen terakhir */
/* ke elemen pertama secara horizontal ke kanan: [en,en-1,...,e2,e1] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [30,20,1] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */