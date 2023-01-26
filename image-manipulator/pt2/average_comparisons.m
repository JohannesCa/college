function ret = average_comparisons(A, M, N)

num = 1/(M*N);  % Mask content 
h = repmat(num, M, N);

tic
G = convolution(A, h);
figure, imshowpair(A, G, 'montage')

execution_time = toc;
disp(['Matrix: (',  num2str(M), ',',  num2str(N), ')'])
disp(['Execution time(s): ',  num2str(execution_time)])

total = numel(G);       % Total elements in matrix
zeros = nnz(~G);        % Number of zero elements

perc_null_pixels = (zeros*100)/total;
disp(['Percentage of null pixels: ',  num2str(perc_null_pixels)])

ret = (G);
end