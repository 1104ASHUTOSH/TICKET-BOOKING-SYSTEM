/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/


#include<bits/stdc++.h>
#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
class TourBus
{       int bid;
	char destination[200];
	char time[50];
	int max_seats;
	int booked;
	int fare;
	public:
	TourBus()
	{
	bid=0;
	max_seats=50;
	booked=0;
	fare=0;
	strcpy(time,"9:10am");
	strcpy(destination,"");
	}
	void input();
	void show();
	void display();
	int getid()
	{
	return bid;
	}
	void book()
	{
	booked++;
	}
	char* getDestination()
	{
	return destination;
	}
	char* getTime()
	{
	return time;
	}
	int getBooked(){
	return booked;
	}
	int getMax(){
	return max_seats;
	}
	int getFare()
	{
		return fare;
	}
};
class Ticket
{
	char name[50];
	TourBus bus;
	public:

	void generate(char cname[], TourBus tb)
	{
		strcpy(name,cname);
		bus=tb;
	}
	void display()
	{
	cout<<"Customer Name "<<name<<endl;
	cout<<"Details of Bus "<<endl;
	bus.show();
		}
};
void TourBus::input()
{
	cout<<"Enter bus id ";
	cin>>bid;
	cout<<"Enter bus destination ";
	gets(destination);
	cout<<"Enter time of bus ";
	cin>>time;
	cout<<"Enter fare of the bus ";
	cin>>fare;
}
void TourBus::display()
{
	cout<<bid<<"\t"<<destination<<"\t"<<time<<"\t"<<max_seats<<"\t"<<booked<<"\t"<<fare<<"\n";
}
void TourBus::show()
{
	cout<<"Bus Id "<<bid<<endl;
	cout<<"Desination "<<destination<<endl;
	cout<<"Time "<<time<<endl;
	cout<<"No. of seats remaining "<<max_seats-booked<<endl;
}
void main()
{
	int ch;
	fstream F,G;
	TourBus b;
	do
	{
		clrscr();
		cout<<"Press 1 - Add a New Tour Bus"<<endl;
		cout<<"Press 2 - Show Selected Bus"<<endl;
		cout<<"Press 3 - Display All Buses"<<endl;
		cout<<"Press 4 - Delete a Bus"<<endl;
		cout<<"Press 5 - Book a ticket "<<endl;
		cout<<"Press 6 - Display Booked Tickets "<<endl;
		cout<<"Press 7 - Exit "<<endl;
		cout<<"Enter your choice ";
		cin>>ch;
		switch(ch)
		{
		case 1:
			F.open("tour.dat",ios::app | ios::binary);
			b.input();
			F.write((char*)&b, sizeof(b));
			F.close();
			cout<<"Bus added Successfully "<<endl;
			getch();
			clrscr();

		break;
		case 2:
			int id,chk=0;
			cout<<"Enter the bus id to be displayed ";
			cin>>id;
			F.open("tour.dat",ios::in | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(b.getid()==id)
					{
						b.show();
						chk=1;
						break;
					}
				}
				if(chk==0)
					cout<<"Bus not Found"<<endl;
			}
			F.close();
			break;


		case 3:
			F.open("tour.dat",ios::in | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
					b.display();
			}
			F.close();
			cout<<"Press a key to continue ";
			getch();
			clrscr();
		break;
		case 4:
			chk=0;
			cout<<"Enter the bus id to be deleted ";
			cin>>id;
			F.open("tour.dat",ios::in | ios::binary);
			G.open("temp.dat",ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(b.getid()!=id)
					{
					G.write((char*)&b,sizeof(b));
					}
					else
					{
						b.show();
						chk=1;

					}
				}
				if(chk==0)
					cout<<"Bus not Found"<<endl;

				else
					cout<<"Bus Deleted "<<endl;
			}
			F.close();
			G.close();
			remove("tour.dat");
			rename("temp.dat","tour.dat");
			break;
		case 5:
			char dest[70],cname[50];
			int bid;
			Ticket t;
			cout<<"Enter the destination ";
			gets(dest);
			F.open("tour.dat",ios::in | ios::out | ios::binary);
			if(F.fail())
				cout<<"Can't open file "<<endl;
			else
			{
				while(F.read((char*)&b,sizeof(b)))
				{
					if(strcmp(b.getDestination(),dest)==0)
					{
						b.show();
						chk=1;
						cout<<"Enter the customer name ";
						gets(cname);
						b.book();
						t.generate(cname,b);
						G.open("tickets.dat",ios::app | ios::binary);
						G.write((char*)&t,sizeof(t));
						G.close();
					F.seekp(F.tellg()-sizeof(b),ios::beg);

					F.write((char*)&b,sizeof(b));
					cout<<"Ticket booked"<<endl;
					getch();
					break;
					}
				}
				if(chk==0)
					cout<<"No Bus Found"<<endl;
					/*	if(b.getid()==id)
						{                  cout<<"booking"<<endl;
						break;
						}     */
			}
			F.close();
			break;
		case 6:
			cout<<"Booked Tickets "<<endl;
			G.open("tickets.dat",ios::in | ios::binary);
			if(G.fail())
				cout<<"can't open file "<<endl;
			else
			{
				while(G.read((char*)&t,sizeof(t)))
				t.display();
			}

			G.close();
			cout<<"Press a key to continue ";
			getch();

		}
	}while(ch!=7);
}
