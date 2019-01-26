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
ylim([-5e3,5e3])
bo=1;
for i=2:length(t)-200
    if bo == 1
        pause;
        bo=0;
    end
    pause(0.01)
    if ~ishandle(h)
        break % Arrete l'animation si la fenetre est fermee
    end
    set(h(1),'YData',f(i,:))
    set(h(2),'YData',A)
    set(ht,'String',sprintf('t=%0.2f s',t(i)))
end


%% Ex 7.2b: Figure analytique-numerique t=tfin
figure
plot(ix(1:263)*dx-500e3,vitesse(1:263))
hold on
plot(x,(-1*A*9.81).^0.5)
grid
xlabel('x [m]')
ylabel('vitesse [m/s]')
xlim([-5e5,5e5])
legend('Numerique','Analytique $u(x) = \sqrt{gh(x)}$')


fichier = 'tsunamiB.out';
subplot(2,2,3)
h(1) = plot(x,f(1,:));
A=arrayfun(@hf,x);

hold on
h(2)= copyobj(h(1),gca); 
% fplot(hf,[min(f(:)),max(f(:))])
% hold off
ylim([min(f(:)),max(f(:))])
ylim([-5e3,5e3])
bo=1;
for i=2:length(t)-200
    if bo == 1
        pause;
        bo=0;
    end
    pause(0.01)
    set(h(1),'YData',f(i,:))
    set(h(2),'YData',A)
    
%% Ex 7.2b: Figure analytique-numerique t=tfin
figure
plot(ix(1:263)*dx-500e3,vitesse(1:263))
hold on
plot(x,(-1*A*9.81).^0.5)
grid
xlabel('x [m]')
ylabel('vitesse [m/s]')
xlim([-5e5,5e5])
legend('Numerique','Analytique $u(x) = \sqrt{gh(x)}$')

