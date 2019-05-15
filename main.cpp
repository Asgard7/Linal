#include<iostream>
#include<iomanip>
using namespace std;

class Vector3D
{
private:
    double x,y,z;

public:
    Vector3D()
    {
        x=y=z=0;
    }
    Vector3D(double x0,double y0,double z0)
    {
        x=x0;
        y=y0;
        z=z0;
    }
    ~Vector3D(){}

    friend Vector3D operator*(double a,Vector3D u);
    Vector3D operator*(double a)
    {
        return Vector3D(a*x,a*y,a*z);
    }
    double operator*(Vector3D u)
    {
        return this->x*u.x+this->y*u.y+this->z*u.z;
    }
    friend Vector3D operator+(Vector3D u,Vector3D v);
    Vector3D operator-(Vector3D u)
    {
        return Vector3D(x-u.x,y-u.y,z-u.z);
    }
    friend   ostream&  operator<< ( ostream&  os ,const  Vector3D& v ) ;

};
Vector3D operator*(double a,Vector3D u)
{
    return Vector3D(a*u.x,a*u.y,a*u.z);
}
Vector3D operator+(Vector3D u,Vector3D v)
{
    return Vector3D(u.x+v.x,u.y+v.y,u.z+v.z);
}
ostream&  operator<<( ostream&  os ,  const   Vector3D&  v )
{
    os  <<  " (" <<v.x<<","<<v.y<<","<<v.z<<")" ;
    return os;
}

class Matrix3D
{
private:
    double** a;

public:
    Matrix3D()
    {
        int i,j;
        a=new double*[3];
        for(i=0;i<3;i++)
            a[i]=new double[3];
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                a[i][j]=0;
    }
    Matrix3D(double** b)
    {
        int i,j;
        a=new double*[3];
        for(i=0;i<3;i++)
            a[i]=new double[3];

        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                a[i][j]=b[i][j];
    }
    Matrix3D(double* b)
    {
        int i,j;
        a=new double*[3];
        for(i=0;i<3;i++)
            a[i]=new double[3];

        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                a[i][j]=b[3*i+j];
    }
    ~Matrix3D()
    {
        for(int i=0;i<3;i++)
            delete[] a[i];
        delete[] a;
    }

    Matrix3D& operator*(double c)
    {
        Matrix3D*  pM=new Matrix3D();
        int i,j;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                pM->a[i][j]=a[i][j]*c;
        return *pM;
    }
    friend Matrix3D& operator*(double c,Matrix3D A);
    Matrix3D& operator+(Matrix3D B)
    {
        Matrix3D* pM=new Matrix3D();
        int i,j;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                pM->a[i][j]=a[i][j] + B.a[i][j];
        return *pM;
    }
    Matrix3D& operator-(Matrix3D B)
    {
        Matrix3D* pM=new Matrix3D();
        int i,j;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
                pM->a[i][j]=a[i][j] - B.a[i][j];
        return *pM;
    }
    Matrix3D& operator*(Matrix3D B)
    {
        Matrix3D* pM=new Matrix3D();
        double s;
        int i,j,k;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                s=0;
                for(k=0;k<3;k++)
                    s+=a[i][k]*B.a[k][j];
                pM->a[i][j]=s;
            }
        return *pM;
    }
    friend   ostream&  operator<< ( ostream&  os ,const Matrix3D& M ) ;

};
Matrix3D& operator*(double c,Matrix3D A)
{
    return A*c;
}
ostream&  operator<<( ostream& os,const  Matrix3D& M)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
            os <<setw(5)<<M.a[i][j];
        cout<<endl;
    }
    cout<<endl;
    return os;
}

int main()
{
    double a=0.1;
    /*Vector3D u(1.2,-2.3,1.0),v(1.2,2,1.0);
    cout<<"u*a = "<<u*a<<endl;
    cout<<"a*u = "<<a*u<<endl;
    cout<<"u*v = "<<u*v<<endl;
    cout<<"u+v = "<<u+v<<endl;
    cout<<"u-v = "<<u-v<<endl;*/
    int i,j;
    double** b=new double*[3];
    for(i=0;i<3;i++)
        b[i]=new double[3];
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            b[i][j]=i+j;

    Matrix3D A(b),B(b);

    cout<<"A= \n"<<A;
    cout<<"B=\n"<<B;
    cout<<"A+B= \n"<<A+B;
    Matrix3D E=A*A;
    cout<<"A*A= \n"<<E;
    double c=0.1;
    cout<<"A = \n"<<A;
    cout<<"A*c= \n"<<A*c;
    cout<<"c*A= \n"<<c*A;
    return 0;
}