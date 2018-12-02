#Arvore de Decisao
tfp1 <- c(0.5 , 0.5 , 0.518519 , 0.6 , 0.606061 , 0.625 , 0.636364 , 0.652174 , 0.703704 , 0.733333)
tvp1 <- c(0.466667 , 0.705882 , 0.655172 , 0.774194 , 0.782609 , 0.6875 , 0.764706 , 0.787879 , 0.931034 , 0.741935)
#Naive Bayers
tfp2 <- c(0, 0.5, 1)
tvp2 = tfp2
#Aleatorio
aleax <- c(0, 1)
aleay = aleax

#plota grafico
plot(tfp1, tvp1, xlab = "TFP", ylab = "TVP", col = "red", main = "Curva ROC", pch = 16, type = "o", xlim = c(0, 1), ylim = c(0, 1))

#Adiciona Naive e Aleatorio
#abline(lines(tfp2, tvp2, pch=18, col="blue", type="o"))
abline(lines(aleax, aleay, pch=18, col="black", type="o"))

#Adiciona legenda
legend(0, 1, legend=c("Arvore Decisão", "Naive Bayers"), col=c("red", "blue"), lty=1:2, cex=0.5)
