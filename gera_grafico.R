#Arvore de Decisao
tfp1 <- c(0.5 , 0.5 , 0.518519 , 0.6 , 0.606061 , 0.625 , 0.636364 , 0.652174 , 0.703704 , 0.733333)
tvp1 <- c(0.466667 , 0.705882 , 0.655172 , 0.774194 , 0.782609 , 0.6875 , 0.764706 , 0.787879 , 0.931034 , 0.741935)
#Naive Bayes
tfp2 <- c(0.480, 0.482, 0.565, 0.656, 0.666, 0.714, 0.733, 0.750, 0.772, 0.833)
tvp2 <- c(0.777, 0.928, 0.852, 0.960, 0.888, 0.805, 0.703, 0.787, 0.800, 0.892)
#Aleatorio
aleax <- c(0, 1)
aleay = aleax

#plota grafico
plot(tfp1, tvp1, xlab = "TFP", ylab = "TVP", col = "red", main = "Curvas ROC", pch = 16, type = "o", xlim = c(0, 1), ylim = c(0, 1))

#Adiciona Naive e Aleatorio
abline(lines(tfp2, tvp2, pch=18, col="blue", type="o"))
abline(lines(aleax, aleay, pch=18, col="black", type="o"))

#Adiciona legenda
legend(0, 1, legend=c("Arvore de Decisão", "Naive Bayes"), col=c("red", "blue"), lty=1:2, cex=0.5)



#######################INTEGRAIS#######################
f = function(x){x}
integralAlAd <- integrate(f, 0.5, 0.733333)
integralAlNb <- integrate(f, 0.480, 0.833)
integrate(lines(tfp2, tvp2, pch=18, col="blue", type="o"), 0.772, 0.833)

integralAD <- 0
integralAD <- integralAD + integrate(reta, 0.5, 0.518519)
integralAD <- integralAD + integrate(reta, 0.518519, 0.6)
integralAD <- integralAD + integrate(reta, 0.6, 0.606061)
integralAD <- integralAD + integrate(reta, 0.606061, 0.625)
integralAD <- integralAD + integrate(reta, 0.625, 0.636364)
integralAD <- integralAD + integrate(reta, 0.636364, 0.652174)
integralAD <- integralAD + integrate(reta, 0.652174, 0.703704)
integralAD <- integralAD + integrate(reta, 0.703704, 0.733333)
AUCAD <- integralAD - integralAlAd

integralNB <- 0
integralNB <- integralNB + integrate(reta, 0.480, 0.482)
integralNB <- integralNB + integrate(reta, 0.482, 0.565)
integralNB <- integralNB + integrate(reta, 0.565, 0.656)
integralNB <- integralNB + integrate(reta, 0.656, 0.666)
integralNB <- integralNB + integrate(reta, 0.666, 0.714)
integralNB <- integralNB + integrate(reta, 0.714, 0.733)
integralNB <- integralNB + integrate(reta, 0.733, 0.750)
integralNB <- integralNB + integrate(reta, 0.750, 0.772)
integralNB <- integralNB + integrate(reta, 0.772, 0.833)
AUCNB <- integralNB - integralAlNb

AUCAD
AUCNB

