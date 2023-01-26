function ret = histogram_equalize(counts, len)
%{
    k = 255.0/(len(1)*len(2))
    temp = zeros(size(counts));
    
    for r = 1:max(size(counts)),
        newpos = floor(k*sum(counts(1:r))) +1;
        temp(newpos) = temp(newpos) + counts(r);
    end

    ret = temp;
%}
    % ref: https://en.wikipedia.org/wiki/Histogram_equalization
    
    k = 255.0/(len(1)*len(2) -1);
    cdf = zeros(max(size(counts)));
    
    for r = 1:max(size(counts)),
        cdf(r) = sum(counts(1:r));
    end
    cdfmin = cdf(find(cdf>0, 1, 'first'));
    
    ret = round(k*(cdf -cdfmin));
end