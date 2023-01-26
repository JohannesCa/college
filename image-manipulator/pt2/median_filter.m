function median_filter(A, n)

[r,c]=size(A);
img1=A;

n1=(n-1)/2;
img2=padarray(img1,[n1,n1]);
n2=((n*n)+1)/2;

for i=n1+1:r+n1
    for j=n1+1:c+n1
        i1=i-n1;
        j1=j-n1;
        z=1;
        for x=i1:i1+n-1
            for y=j1:j1+n-1
                arr(z)=img2(x,y);
                z=z+1;
            end
        end
        
        arr1=sort(arr);
        img2(i,j)=arr1(n2);
    end
end
 
img3=img2(n1+1:r,n1+1:c);
d=img3;

figure, imshowpair(A, uint8(d), 'montage');
suptitle('Filtro de Mediana');

end