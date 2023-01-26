function edge_detection_filter(A, b)

if b == 1
    h = [ -1/8,    -1/8,   -1/8;
          -1/8,      1,    -1/8;
          -1/8,    -1/8,   -1/8];

elseif b == 2
    h = [-1,       -1,     -1;
          0,        0,      0;
          1,        1,      1];
      
elseif b == 3
    h = [ -1,       0,      1;
          -1,       0,      1;
          -1,       0,      1];
      
elseif b == 4
    h = [ -1,     -1,     0;
          -1,      0,     1;
           0,      1,     1];
end

G = convolution(A, h);
figure, imshowpair(A, G, 'montage')

test = imfilter(A, h, 'conv');
figure, imshowpair(A, test,'montage')

end