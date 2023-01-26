function ret = histogram_expand(counts)
    rmin = find(counts>0, 1, 'first');
    rmax = find(counts>0, 1, 'last');
    temp = zeros(size(counts));
    
    for r = rmin:rmax,
        newpos = round((double(r - rmin)/double(rmax - rmin))*255) +1;
        temp(newpos) = counts(r);
    end
    
    ret = temp;
end