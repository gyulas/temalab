%% derive (difference)
dy_hn2=zeros(700,1);
for i=1:700
    dy_hn2(i)=yhn2(i+1)-yhn2(i)
end


%% integrate (sum)
iy_hn2=zeros(700,1);
for i=1:700
    iy_hn2(i)=sum(yhn2(1:i));
end