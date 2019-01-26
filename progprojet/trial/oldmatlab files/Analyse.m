set(groot, 'defaultAxesTickLabelInterpreter','latex');
set(groot, 'defaultLegendInterpreter','latex');
set(groot, 'defaultTextInterpreter', 'latex');
set(groot, 'defaultAxesFontSize', 18);



%% Chargement des resultats %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fichier = 'tsunamiB.out';
data = load([fichier,'_u']);
x = data(:,1);
u = data(:,2);
data = load([fichier,'_E']);
t = data(:,1);
E = data(:,2);
data = load([fichier,'_f']);
f = data(:,2:end);
dt= load([fichier,'_dt']);

%% Figures %%
%%%%%%%%%%%%%
figure('Name',['Analyse de ' fichier])
subplot(2,2,1)
plot(x,u)
grid
xlabel('x [m]')
ylabel('u [m/s]')

subplot(2,2,2)
plot(t,E)
grid
xlabel('t [s]')
ylabel('E [m $^3$ ]')

subplot(2,2,4)
[X,T] = meshgrid(x,t);
pcolor(X,T,f)
shading interp
colormap jet
c = colorbar;
xlabel('x [m]')
ylabel('t [s]')
ylabel(c,'f(x,t) [m]')

subplot(2,2,3)
h(1) = plot(x,f(1,:));
A=arrayfun(@hf,x);

hold on
h(2)= copyobj(h(1),gca); 
% fplot(hf,[min(f(:)),max(f(:))])
% hold off
grid
xlabel('x [m]')
ylabel('f(x,t) [m]')
ht = title('t=0 s');
ylim([min(f(:)),max(f(:))])
bo=1;
for i=2:length(t)
    if bo == 1
        pause;
        bo=0;
    end
    pause(0.001)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
    set(h(1),'YData',f(i,:))
    set(h(2),'YData',A)
    set(ht,'String',sprintf('t=%0.2f s',t(i)))
end
%% Figures separee
figure
plot(x,u)
grid
xlabel('x [m]')
ylabel('u [m/s]')

figure
[X,T] = meshgrid(x,t);
pcolor(X,T,f)
shading interp
colormap jet
c = colorbar;
xlabel('x [m]')
ylabel('t [s]')
ylabel(c,'f(x,t) [m]')

figure
A=arrayfun(@hf,x);
plot(x,A);
xlabel('x [m]')
ylabel('h [m]')

figure
plot(x,f(size(f,1),:))
grid
xlabel('x [m]')
ylabel('f(x,t) [m]')

%% Ex 7.2b: Figure analytique-numerique t=tfin


plot(x,-4*sin((1*pi/20).*(x+5)))
hold on 
plot(x,f(size(f,1),:))
%analytique
grid on
xlabel('x [m]')
ylabel('f(x,t) [m]')
legend('Analytique','Numerique')

%% Analyse de crete
for i = 1:size(f(:,1))
  [M,I] = max(f(i,:));
  It(i) =I;
  bo =0;
  if (I  == (size(f(i,:),2)) && bo ==0) 
    tc= i*30000/size(f,1);
    bo=1;
    i
  end
end
tc
%% Analyse d'amplitude: cas A
figure
grid
hold on
xlabel('x [m]')
ylabel('max A [m]')
plot(x,(max(f,[],1)-min(f,[],1))/2)
A=arrayfun(@hf,x);
plot(x,9.81^(-1)*(-1*A).^0.25)
legend('maxA','$A_0 \times h(x)^{\frac{1}{4}}$ ')

%% Analyse d'amplitude: cas B
figure
grid
hold on
xlabel('x [m]')
ylabel('max A [m]')
plot(x,(max(f,[],1)-min(f,[],1))/2)
A=arrayfun(@hf,x);
plot(x,9.81*(-1*A).^-0.25)
legend('maxA','$A_0 \times h(x)^{\frac{-1}{4}}$ ')

%% Analyse de vitesse
xpeak= ones(size(f(:,1)));
ix = ones(size(f(:,1)));
for i=1:size(f,1)
    [xpeak(i),ix(i)]= max(f(i,:));
end

vitesse= ones(size(f(:,1)));
dx= 2*500e3 /size(x,1);
for i=1:size(f(:,1))-1
    vitesse(i)=(ix(i+1)-ix(i))*dx/(30000/size(f,1));
end
figure
plot(ix(1:263)*dx-500e3,vitesse(1:263))
hold on
plot(x,(-1*A*9.81).^0.5)
grid
xlabel('x [m]')
ylabel('vitesse [m/s]')
xlim([-5e5,5e5])
legend('Numerique','Analytique $u(x) = \sqrt{gh(x)}$')
