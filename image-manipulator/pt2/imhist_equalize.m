function imhist_equalize(image)
    aux = zeros(size(image));
    channel = 'RGB';
    k = 255.0/(size(image, 1)*size(image, 2)); % 255/RC
    
    figure, subplot(2,4,1);
    imhist(rgb2gray(image));
    title('Grayscale');
    grid on
    
    for i = 1:3,
        % Calculations
        [counts, binLoc] = imhist(image(:,:,i));
        counts = histogram_equalize(counts, size(image));
        
        for r = 1:size(aux, 1),
            for c = 1:size(aux, 2),
                %aux(r,c,i) = round(k*sum(counts(1:double(image(r,c,i))))) +1;
                aux(r,c,i) = counts(image(r,c,i) +1);
            end
        end

        % Ploting
        subplot(2,4,i+1);
        imhist(image(:,:,i));
        title(channel(i));
        grid on
        
        subplot(2,4,i+5);
        imhist(uint8(aux(:,:,i)));
        title(channel(i));
        grid on
    end
    G = uint8(aux);
    
    subplot(2,4,5);
    imhist(rgb2gray(G));
    title('Grayscale');
    grid on
    suptitle('Equalização de Histograma (histogramas)');
    
    pause;
    
    figure, subplot(1,2,1); imshow(image); title('Original');
    subplot(1,2,2); imshow(G); title('Equalizada');
    suptitle('Equalização de Histograma (comparação)');
end