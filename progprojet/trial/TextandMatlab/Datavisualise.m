%%Text format%%
set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);

%%Analysis%%

%%Unpack Data%%
nsimul = 1000;
%variable glossary:
%E = energy
%C = correlation
%A = total angle
%T = type
  %m_T = magnet type = ff,fw,ww
  %v_T = magnet types on a vertex (x3)
  %d_T = magnet types on a double vertex (x5)
  %f_T = magnet types on a face (x5)
%O = face orientation = 5,4,3,2


%% system
load('data/evolve/angles'); %nx(T,E,C,ax30)
s = angles;
s_a = s(:,4:33);
for i = 1:nsimul
    for j = 1:30
        s_a(i,j) = mod(s_a(i,j),pi);
    if s_a(i,j)>pi/2
        q = s_a(i,j);
        s_a(i,j) = pi - q;
        s_a(i,j) = mod(s_a(i,j),pi);
    end
    end
end
s_Aabs = sum(abs(s_a),2);
s_A = sum(s_a,2);
s_E = s(:,2);
s_C = s(:,3); %maybe need a couple of different correlations


figure %histograms of energy, correlation & angle
subplot(1,3,1)
histogram(s_E,10);
grid on
title('E');
subplot(1,3,2)
histogram(s_C,10);
grid on
title('C');
subplot(1,3,3)
grid on
%histogram(mod(s_Aabs,pi),100)
histogram(s_Aabs,30)

title('A')

figure %scatter E vs C, E vs A
subplot(1,2,1)
hold on
scatter(s_C,s_E);
R = corrcoef(s_C,s_E);
grid on
xlabel('cor');
ylabel('E');
subplot(1,2,2)
hold on
scatter(mod(s_Aabs,pi),s_E);
grid on
xlabel('angle')
ylabel('E')
%% magnets
load('data/evolve/magnets'); %nx30x(a,T)
m = reshape(magnets,[250,30,2]);
m_A = m(:,:,1);
m_T = m(:,:,2);

m_ff_A = zeros(250*30,2); %11411, 12411, 12421, (angle,type)
m_fw_A = zeros(250*30,2);
m_ww_A = zeros(250*30,2);
m_fff_A = zeros(size(m_A));

for i = 1:nsimul
  for j = 1:30
      q = m_T(i,j);

      m1 = int32(q/10000);
      m2 = int32(mod(q,10000)/1000);
      m3 = int32(mod(q,1000)/100);
      m4 = int32(mod(q,100)/10);
      m5 = int32(mod(q,10));
      ms = [m1,m2,m3,m4,m5];

    if m3 == 4 %strong
      n3 = nnz(ms==3);
      n2 = nnz(ms==2);
      n1 = nnz(ms==1);
      m_ff_A(i*j,1) = m_A(i,j);

      if n2 == 3
          m_ff_A(i*j,2) = 22421;
      elseif n1 == 3
          m_ff_A(i*j,2) = 11412;
      elseif n1 == 2 && n2 == 2
          if m1 == m2
              m_ff_A(i*j,2) = 11422;
          else
              m_ff_A(i*j,2) = 12412;
          end
      else
          m_ff_A(i*j,2) = q;
      end

    elseif m3 == 3 %strong-weak
     m_fw_A(i*j,1) = m_A(i,j);
     m_fw_A(i*j,2) = q;
    elseif m3 == 2 %strong-weak
     m_fw_A(i*j,1) = m_A(i,j);
     m_fw_A(i*j,2) = q;
    elseif m3 == 1 %weak
      ms(ms==3)=2;
      q = 10000*ms(1)+ 1000*ms(2)+100*ms(3)+10*ms(4)+ms(5);
      m_ww_A(i*j,1) = m_A(i,j);
      n2 = nnz(ms==2);
      n1 = nnz(ms==1);
      n4 = nnz(ms==4);
      if n2 == 3
        if n1 == 2
          m_ww_A(i*j,2) = 22121;
        elseif n1 == 1
          m_ww_A(i*j,2) = 22124;
        end
      elseif n1 == 3
          if n4 == 0
              m_ww_A(i*j,2) = 12121;
          elseif n4 ==1
              m_ww_A(i*j,2) = 14121;
          else
              m_ww_A(i*j,2) = 14141;
          end
      elseif m(1)==2 && m(2)==2
           m_ww_A(i*j,2) = 22141;
      elseif m(4)==2 && m(5)==2
           m_ww_A(i*j,2) = 22141;
      elseif n4 == 2
           m_ww_A(i*j,2) = 41124;
      elseif n1==n2
           m_ww_A(i*j,2) = 12124;


      else
        m_ww_A(i*j,2) = q;
     end
    end
  end
end

x = m_ff_A;

for i = 1:length(x)
    if x(i,1) == 0
        x(i,:) = 0;
    end
    x(i,1) = mod(x(i,1),pi);
    if x(i,1)>pi/2
        q = x(i,1);
        x(i,1) = pi - q;
        x(i,1) = mod(x(i,1),pi);
    end

end

C = unique(x(:,2));
A = zeros(length(x),length(C));
A = A*nan;
count = 0;
for i = 1:length(x)
    for j = 1:length(C)
        if x(i,2) == C(j)
            if C(j) == 11411
                count = count+1;
            end
            A(i,j) = x(i,1);
        end
    end
end
A(A==0) = nan;


figure
hist(A(:,2:length(C)));
colormap jet
grid on
xlabel('angle');
title('ff');
legend(num2str(C(2:length(C))));



%% Youssef: Face types


load('data/evolve/faces'); %n*12*(central magnets, numberoftypes, face orientation, Energy)
%f= reshape(faces, [12*nsimul,10]);
f= zeros(12*nsimul,10);
for i= 1:length(faces)
    for j = (i*12 -11): i*12
        f(j,:) = faces(i,mod(j-1,12)+1,:);
    end
end


%face energy:

figure
C = unique(f(:,6));
A = zeros(length(f),length(C));
A = A*nan;
for i = 1:length(f)
    for j = 1:length(C)
        if f(i,6) == C(j)
            A(i,j) = f(i,10);
        end
    end
end
A(A==0) = nan;

xbins = -50:50;
xbins = xbins*10^-6;
hist(A(:,1:length(C)), xbins);
colormap jet
grid on
ylabel('Count');
xlabel('Energy')
title('Energy and number of weaks on face');
legend(num2str(C(1:length(C))));

%Energy and Face type
figure
C = unique(f(:,9));
A = zeros(length(f),length(C));
A = A*nan;
for i = 1:length(f)
    for j = 1:length(C)
        if f(i,9) == C(j)
            A(i,j) = f(i,10);
        end
    end
end
A(A==0) = nan;

hist(A(:,1:length(C)),xbins);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Energy and Face type');
legend(num2str(C(1:length(C))));

%FF and Face type
figure
C = unique(f(:,9));
A = zeros(length(f),length(C));
A = A*nan;
for i = 1:length(f)
    for j = 1:length(C)
        if f(i,9) == C(j)
            A(i,j) = f(i,8);
        end
    end
end
%A(A==0) = nan;

hist(A(:,1:length(C)));
colormap jet
grid on
xlabel('Faceorientation');
ylabel('Count')
title('FF-Facetype');
legend(num2str(C(1:length(C))));

%Detailed face types:
detailedfacetypes= f(:,1);

for i = 1:length(f)
    detailedfacetypes(i)=  f(i,6) + f(i,7)*10 +f(i,8)*100 + abs(f(i,9))*1000 ;
end

figure
xbin = 0:15000;
hist(detailedfacetypes,xbin);
colormap jet
grid on
xlabel('Face types (detailed)');
ylabel('Count')
title('Detailed Face types');

uniqueDetFacetypes = unique(detailedfacetypes);


%Energy and detailed Face type
figure
C = uniqueDetFacetypes;
A = zeros(length(f),length(C));
A = A*nan;
for i = 1:length(f)
    for j = 1:length(C)
        if detailedfacetypes(i) == C(j)
            A(i,j) = f(i,10);
        end
    end
end
%A(A==0) = nan;

hist(A(:,1:length(C)),xbins);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Energy and Face type(detailed)');
legend(num2str(C(1:length(C))));


%% Youssef: Dodec types (with detailed face types)
dodecstg2 = zeros(length(faces),1);
for i =1:(length(faces))
    for j = (i*12 -11): (i*12)
        for l = 1:length(uniqueDetFacetypes)
            if uniqueDetFacetypes(l) == detailedfacetypes(j)
                dodecstg2(i)= dodecstg2(i) + 10^(l-1);
            end
        end
    end
end
uniquepossibleconfigurations2 = unique(dodecstg2);

%Dodec configuration and Energy
C = uniquepossibleconfigurations2;
A = zeros(length(angles),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if dodecstg2(i) == C(j)
            A(i,j) = angles(i,2);
        end
    end
end

figure
hist(A(:,1:length(C)));
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Energy - Dodec configuration');
legend(num2str(C(1:length(C))));


%% Youssef: Dodec types (with basic face types)
%for every orientation equal and opposite orientation:
load('data/evolve/dodecs'); %n*dodectype
figure
xbins = 0:60;
hist(dodecs,xbins);
colormap jet
grid on
xlabel('Dodec type');
ylabel('Count')
title('Dodec types');
legend('10 -10','3 -3', '2 -2', '1 -1');

% grouping
dodecsg = dodecs;
for i = 1:length(dodecs)
   for j = 1:4
       d1 = floor(dodecs(i,j)/10);
       d2 = int16(mod(dodecs(i,j),10));
       dodecsg(i,j) = min(d2,d1)*10 + max(d1,d2);
   end
end
figure
xbins = 0:60;
hist(dodecsg,xbins);
colormap jet
grid on
xlabel('Dodec type (grouped)');
ylabel('Count')
title('Dodec types');
legend('10 -10','3 -3', '2 -2', '1 -1');

%total grouping:

dodecstg = dodecs(:,1);
for i = 1:length(dodecs)
       d1 = floor(dodecs(i,1)/10);
       d2 = int16(mod(dodecs(i,1),10));
       dodecstg(i) = (d1+d2)*1000;
       d1 = floor(dodecs(i,2)/10);
       d2 = int16(mod(dodecs(i,2),10));
       dodecstg(i) = dodecstg(i) +(d1+d2)*100;
       d1 = floor(dodecs(i,3)/10);
       d2 = int16(mod(dodecs(i,3),10));
       dodecstg(i) = dodecstg(i) +(d1+d2)*10;
       d1 = floor(dodecs(i,4)/10);
       d2 = int16(mod(dodecs(i,4),10));
       dodecstg(i) = dodecstg(i) +(d1+d2)*1;
end
figure
xbins = 0:7100;
hist(dodecstg,xbins);
colormap jet
grid on
xlabel('Dodec type (totally grouped, defects 2-2-0)');
ylabel('Count')
title('Dodec types');
uniquepossibleconfigurations= unique(dodecstg);

%Dodec configuration and Energy

C = uniquepossibleconfigurations;
A = zeros(length(angles),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if dodecstg(i) == C(j)
            A(i,j) = angles(i,2);
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Energy - Dodec configuration');
legend(num2str(C(1:length(C))));

%% Youssef: Detailled Dodec:
%total groupingdetailed:

dodecstgd = dodecs(:,1);
for i = 1:length(dodecs)
    d1 = floor(dodecs(i,1)/10);
    d2 = int64(mod(dodecs(i,1),10));
    %        dodecstgd(i) = (d1+d2)*(d1+d2+1)/2 +d2;
    d3 = floor(dodecs(i,2)/10);
    d4 = int64(mod(dodecs(i,2),10));
    %        dodecstgd(i) = dodecstg(i) +((d3+d4)*(d3+d4+1)/2 +d4)*100;
    d5 = floor(dodecs(i,3)/10);
    d6 = int64(mod(dodecs(i,3),10));
    %        dodecstgd(i) = dodecstg(i) +((d5+d6)*(d5+d6+1)/2 +d6)*10000;
    d7 = floor(dodecs(i,4)/10);
    d8 = int64(mod(dodecs(i,4),10));
%        dodecstgd(i) = dodecstg(i) +((d7+d8)*(d7+d8+1)/2 +d8)*1000000;
%        a =0;
%        if(d1> d2)
%            a=1;
%        end
%        if(d2> d1)
%            a=2;
%        end
%        dodecstgd(i) = dodecstg(i)+a*1000000;


    dodecstgd(i) = dodecs(i,1)*1000000;
    dodecstgd(i) = dodecstgd(i) +dodecs(i,2)*10000;

    dodecstgd(i) = dodecstgd(i) +dodecs(i,3)*100;

    dodecstgd(i) = dodecstgd(i) +dodecs(i,4)*1;
end
uniquepossibleconfigurationsd= unique(dodecstgd);
indexeddodecs = dodecstgd;
for i = 1:length(dodecstgd)
    for j = 1:length(uniquepossibleconfigurationsd)
        if(uniquepossibleconfigurationsd(j) == dodecstgd(i) )
            indexeddodecs(i) =j;
        end
    end
end


% Now accounting for symmetry:
uniquepossibleconfigurationsdSym = uniquepossibleconfigurationsd ;
for i =1: length(uniquepossibleconfigurationsdSym)
    d1i = floor(mod(uniquepossibleconfigurationsdSym(i),10));
    d2i = floor(mod(uniquepossibleconfigurationsdSym(i),100)/10);
    d3i = floor(mod(uniquepossibleconfigurationsdSym(i),1000)/100);
    d4i = floor(mod(uniquepossibleconfigurationsdSym(i),10000)/1000);
    d5i = floor(mod(uniquepossibleconfigurationsdSym(i),10^5)/10^4);
    d6i = floor(mod(uniquepossibleconfigurationsdSym(i),10^6)/10^5);
    d7i = floor(mod(uniquepossibleconfigurationsdSym(i),10^7)/10^6);
    d8i = floor(mod(uniquepossibleconfigurationsdSym(i),10^8)/10^7);
    for j =1: length(uniquepossibleconfigurationsdSym)
        d1j= floor(mod(uniquepossibleconfigurationsdSym(j),10));
        d2j= floor(mod(uniquepossibleconfigurationsdSym(j),100)/10);
        d3j= floor(mod(uniquepossibleconfigurationsdSym(j),1000)/100);
        d4j= floor(mod(uniquepossibleconfigurationsdSym(j),10000)/1000);
        d5j = floor(mod(uniquepossibleconfigurationsdSym(j),10^5)/10^4);
        d6j= floor(mod(uniquepossibleconfigurationsdSym(j),10^6)/10^5);
        d7j= floor(mod(uniquepossibleconfigurationsdSym(j),10^7)/10^6);
        d8j= floor(mod(uniquepossibleconfigurationsdSym(j),10^8)/10^7);
        if i~= j && d1i == d2j && d1j == d2i && d3i == d4j && d3j == d4i && d5i == d6j && d5j == d6i && d7i == d8j && d7j == d8i
            uniquepossibleconfigurationsdSym(j) = uniquepossibleconfigurationsdSym(i);
        end

    end
end
uniquepossibleconfigurationsdSym = unique(uniquepossibleconfigurationsdSym);
uniquepossibleconfigurationsdSymWithsum= [uniquepossibleconfigurationsdSym zeros(length(uniquepossibleconfigurationsdSym ),1)];
for i =1: length(uniquepossibleconfigurationsdSym)
    d1i = floor(mod(uniquepossibleconfigurationsdSym(i),10));
    d2i = floor(mod(uniquepossibleconfigurationsdSym(i),100)/10);
    d3i = floor(mod(uniquepossibleconfigurationsdSym(i),1000)/100);
    d4i = floor(mod(uniquepossibleconfigurationsdSym(i),10000)/1000);
    d5i = floor(mod(uniquepossibleconfigurationsdSym(i),10^5)/10^4);
    d6i = floor(mod(uniquepossibleconfigurationsdSym(i),10^6)/10^5);
    d7i = floor(mod(uniquepossibleconfigurationsdSym(i),10^7)/10^6);
    d8i = floor(mod(uniquepossibleconfigurationsdSym(i),10^8)/10^7);
    uniquepossibleconfigurationsdSymWithsum(i,2)= d1i+d2i + 10*(d3i+d4i) + 100*(d5i+d6i) + 1000*(d7i+d8i);
end
uniquepossibleconfigurationsdSymWithsum = [uniquepossibleconfigurationsdSymWithsum ,zeros(length(uniquepossibleconfigurationsdSymWithsum),1)];
for i= 1:length(uniquepossibleconfigurationsdSymWithsum)
    for j= 1:length(uniquepossibleconfigurationsdSymWithsum)
       if uniquepossibleconfigurationsdSymWithsum(i,2) == uniquepossibleconfigurationsdSymWithsum(j,2) && i~=j
           uniquepossibleconfigurationsdSymWithsum(i,3) =uniquepossibleconfigurationsdSymWithsum(i,3)+1;
           %uniquepossibleconfigurationsdSymWithsum(j,3) =uniquepossibleconfigurationsdSymWithsum(j,3)+1;
       end
    end
end
figure
xbins = 0:55;
hist(indexeddodecs,xbins);
colormap jet
grid on
xlabel('Dodec type (indexed)');
ylabel('Count')
title('Dodec types');



%Dodec configuration and Energy

C = uniquepossibleconfigurationsdSym;
A = zeros(length(angles),length(C));
A = A*nan;
for i = 1:length(angles)
    d1 = floor(dodecs(i,1)/10);
    d2 = int64(mod(dodecs(i,1),10));
    d3 = floor(dodecs(i,2)/10);
    d4 = int64(mod(dodecs(i,2),10));
    d5 = floor(dodecs(i,3)/10);
    d6 = int64(mod(dodecs(i,3),10));
    d7 = floor(dodecs(i,4)/10);
    d8 = int64(mod(dodecs(i,4),10));
    for j = 1:length(C)
        d1j= floor(mod(uniquepossibleconfigurationsdSym(j),10));
        d2j= floor(mod(uniquepossibleconfigurationsdSym(j),100)/10);
        d3j= floor(mod(uniquepossibleconfigurationsdSym(j),1000)/100);
        d4j= floor(mod(uniquepossibleconfigurationsdSym(j),10000)/1000);
        d5j = floor(mod(uniquepossibleconfigurationsdSym(j),10^5)/10^4);
        d6j= floor(mod(uniquepossibleconfigurationsdSym(j),10^6)/10^5);
        d7j= floor(mod(uniquepossibleconfigurationsdSym(j),10^7)/10^6);
        d8j= floor(mod(uniquepossibleconfigurationsdSym(j),10^8)/10^7);
        if d1 == d2j && d1j == d2 && d3 == d4j && d3j == d4 && d5 == d6j && d5j == d6 && d7 == d8j && d7j == d8
            A(i,j) = angles(i,2);
        end
        if uniquepossibleconfigurationsdSym(j) == dodecstgd(i)
             A(i,j) = angles(i,2);
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Energy - Dodec configuration (with symmetry)');
legend(num2str(C(1:length(C))));

%Dodec configuration and FF (temp)

%faces120 =reshape(face, [nsimul, 12*10]);

C = uniquepossibleconfigurationsd;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if  C(j) == dodecstgd(i)
            A(i,j) =0;
            for l = 1:12
                A(i,j) = A(i,j)+ faces(i,l,8);
            end
            A(i,j) = A(i,j)/2;
        end
    end
end
FFdodecnonunique = A;
FFDodec = unique(A);
FFDodec(isnan(FFDodec)) = FFDodec(1);
FFDodec = unique(FFDodec);

figure
xbins = 0:25;
hist(A,xbins);
colormap jet
grid on
xlabel('FF');
ylabel('Count')
title('FF - Dodec configuration');
legend(num2str(C(1:length(C))));


%FF energy

C = FFDodec;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        tmp =0;
            for l = 1:12
                tmp = tmp + faces(i,l,8);
            end
            tmp = tmp/2;
            if tmp == FFDodec(j)
                A(i,j) = angles(i,2);
            end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('FF - Energy');
legend(num2str(C(1:length(C))));

%Dodec configuration and WW (temp)

%faces120 =reshape(face, [nsimul, 12*10]);

C = uniquepossibleconfigurationsd;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if  C(j) == dodecstgd(i)
            A(i,j) =0;
            for l = 1:12
                A(i,j) = A(i,j)+ faces(i,l,6);
            end
            A(i,j) = A(i,j)/2;
        end
    end
end

WWDodec = unique(A);
WWDodec(isnan(WWDodec)) = WWDodec(1);
WWDodec = unique(WWDodec);

figure
xbins = 0:25;
hist(A,xbins);
colormap jet
grid on
xlabel('WW');
ylabel('Count')
title('WW - Dodec configuration');
legend({num2str(C(1:length(C)))});


%WW energy

C = WWDodec;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        tmp =0;
        for l = 1:12
            tmp = tmp + faces(i,l,6);
        end
        tmp = tmp/2;
        if tmp == WWDodec(j)
            A(i,j) = angles(i,2);
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('WW - Energy');
legend(num2str(C(1:length(C))));



%FF-WW

C = WWDodec;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
                tmp =0;
            for l = 1:12
                tmp = tmp + faces(i,l,6);
            end
            tmp = tmp/2;

        if  C(j) == tmp
            A(i,j) =0;
            for l = 1:12
                A(i,j) = A(i,j)+ faces(i,l,8);
            end
            A(i,j) = A(i,j)/2;
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('FF');
ylabel('Count')
title('WW - FF');
lgd = legend(num2str(C(1:length(C))));
title(lgd,'WW')

%Orientation sum Dodec type
Orientationsum = zeros(length(dodecs),length(uniquepossibleconfigurationsd));
Orientationsum = Orientationsum*nan;
for i = 1:length(dodecs)
       d1 = floor(dodecs(i,1)/10);
        d2 = int64(mod(dodecs(i,1),10));
      d3 = floor(dodecs(i,2)/10);
       d4 = int64(mod(dodecs(i,2),10));
      d5 = floor(dodecs(i,3)/10);
      d6 = int64(mod(dodecs(i,3),10));
       d7 = floor(dodecs(i,4)/10);
       d8 = int64(mod(dodecs(i,4),10));
       Osum = (d1-d2)*5 + (d3-d4)*4 + (d5-d6)*3 + (d7-d8)*1;
    for j=1:length(uniquepossibleconfigurationsd)
        if(uniquepossibleconfigurationsd(j) == dodecstgd(i) )
            Orientationsum(i,j) =Osum;
        end
    end
end

figure
xbins = -11:11;
hist(Orientationsum(:,1:length(uniquepossibleconfigurationsd)),xbins);
colormap jet
grid on
xlabel('Orientation sum');
ylabel('Count')
title('Orientation sum - Dodec type');
lgd = legend(num2str(uniquepossibleconfigurationsd(1:length(uniquepossibleconfigurationsd))));
title(lgd,'Dodec type')


%% Youssef: Orientationsum Energy and FF

Orientationsum2 = zeros(nsimul,1);
for i = 1:length(dodecs)
       d1 = floor(dodecs(i,1)/10);
        d2 = int64(mod(dodecs(i,1),10));
      d3 = floor(dodecs(i,2)/10);
       d4 = int64(mod(dodecs(i,2),10));
      d5 = floor(dodecs(i,3)/10);
      d6 = int64(mod(dodecs(i,3),10));
       d7 = floor(dodecs(i,4)/10);
       d8 = int64(mod(dodecs(i,4),10));
       Osum = (d1-d2)*5 + (d3-d4)*4 + (d5-d6)*3 + (d7-d8)*1;
       Orientationsum2(i) = Osum;
end

C = unique(Orientationsum2);
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if(Orientationsum2(i) == C(j))
            A(i,j) =angles(i,2);
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Osum - Energy');
lgd = legend(num2str(C(1:length(C))));
title(lgd,'Osum')

%FF-Osum
C = unique(Orientationsum2);
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if(Orientationsum2(i) == C(j))
            tmp =0;
            for l = 1:12
                tmp = tmp + faces(i,l,8);
            end
            A(i,j) =tmp/2;
        end
    end
end

figure
hist(A);
colormap jet
grid on
xlabel('FF');
ylabel('Count')
title('Osum - FF');
lgd = legend(num2str(C(1:length(C))));
title(lgd,'Osum')

%% Youssef: moredetailed dodecconfig
load('data/evolve/dodecs');
dodecstgdmore = dodecs(:,1);
weird = [];
for i = 1:length(dodecs)
        dodecstgdmore(i) = dodecs(i,1);
        dodecstgdmore(i) = dodecstgdmore(i) +dodecs(i,2)*100;

        dodecstgdmore(i) = dodecstgdmore(i) +dodecs(i,3)*10000;

        dodecstgdmore(i) = dodecstgdmore(i) +dodecs(i,4)*1000000;
        numberofFF =0;
        for l = 1:12
                numberofFF = numberofFF + faces(i,l,6);

        end
        numberofFF = numberofFF/2;
        dodecstgdmore(i) = dodecstgdmore(i) + numberofFF*100000000;
end
uniquepossibleconfigurationsdmore= unique(dodecstgdmore);
indexeddodecsmore = dodecstgdmore;
for i = 1:length(dodecstgdmore)
    for j = 1:length(uniquepossibleconfigurationsdmore)
        if(uniquepossibleconfigurationsdmore(j) == dodecstgdmore(i) )
            indexeddodecsmore(i) =j;
        end
    end
end

figure
xbins = 0:550;
hist(indexeddodecsmore,xbins);
colormap jet
grid on
xlabel('Dodec type more detailed (indexed)');
ylabel('Count')
title('Dodec types (more detailed)');

%Energy
C = uniquepossibleconfigurationsdmore;
A = zeros(length(faces),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        if dodecstgdmore(i) == uniquepossibleconfigurationsdmore(j)
            A(i,j) = angles(i,2);
        end

    end
end

figure
hist(A);
colormap jet
grid on
xlabel('Energy');
ylabel('Count')
title('Detailed dodec - Energy');
legend(num2str(C(1:length(C))));

%% FF and WW and FW and WF
%FF v. number of perfect faces:
C = FFDodec;
A = zeros(length(dodecs),length(C));
A = A*nan;
for i = 1:length(angles)
    for j = 1:length(C)
        d1 = int64(dodecs(i,1)/10);
        d2 = int64(mod(dodecs(i,1),10));
        numberofperfectfaces=d1+d2;
        numberofFF =0;
        for l = 1:12
            numberofFF = numberofFF + faces(i,l,8);
        end
        numberofFF = numberofFF/2;
        if C(j) == numberofFF
            A(i,j) = numberofperfectfaces;
        end
    end
end

figure
xbin = 0:6;
hist(A,xbin);
colormap jet
grid on
xlabel('Numberofperfectfaces');
ylabel('Count')
title('FF - Numberofperfectfaces');
lgd = legend(num2str(C(1:length(C))));
title(lgd,'FF')




%%

%vertices
load('data/evolve/vertices'); %nx30x(a,T)
v = reshape(vertices,[250,20,2]);%v_A = v(:,:,1:3);
%v_T = v(:,:,4:6);
v_E = v(:,:,1);

figure
histogram(v_E,20)



%%
%doublevertices
d = load('data/doublevertices'); %shape:(nsimul)x(30)x(anglex5,typex5,E)
d_A = d(:,:,1:5);
d_T = d(:,:,6:10);
d_E = d(:,:,11);

%faces
f = load('data/faces'); %shape:(nsimul)x(12)x(anglex5,Vtypex5,O,E)
f_A= f(:,:,1:5);
f_T = f(:,:,6:10);
f_E = f(:,:,11);
f_O = f(:,:,12);

%%%%%%% PLOTS %%%%%%%

%%scatter frequency plots%%
%s: all
%m: A, ff_A, fw_A, ww_A


%%histograms%%
%m_T
%v_T
%d_T
%f_T & f_T for each f_O

%%Gaussians (Box plots, show mean and std)%%
%T vs E for m,v,d,f

%%dependencies / correlations%%
%s: A, Aabs vs E
%s: A, Aabs vs C
%s: C vs E
%f_O vs f_E & f_O vs s_E

%think of good way to visualise frequency of face types, eg
%12 faces, each with one of four configs. Easiest is freq: number of perf faces


% function y = modpi(x)
%      x = x(x ~= 0);
%     x = mod(x,pi);
%     for i = 1:length(x)
%     if x(i)>pi/2
%         q = x(i);
%         x(i) = pi - q;
%     end
%     end
%     x = mod(x,pi);
%     y = x;
% end
