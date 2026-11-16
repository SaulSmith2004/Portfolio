# Question 5: Glass Manufacturer Coating Analysis

# Load the data
lenses <- read.csv("lenses.csv")
lenses$Coating <- factor(lenses$Coating)

# Part (a) 1 & 2: Descriptive Stats and Boxplot
library(mosaic)



favstats(impairment ~ Coating, data=lenses)

boxplot(impairment ~ Coating, data=lenses, 
        main="Lens Impairment by Coating Type",
        xlab="Impairment Score (Lower is Better)", 
        col=c("blue", "green", "red", "yellow"),
        horizontal=TRUE)



# Part (b) 1: Statistical Testing

# 1. Checking Normality for each group
# H0: Data is normally distributed
tapply(lenses$impairment, lenses$Coating, shapiro.test)

# 2. Check for Equal Variance
# H0: Variances are equal
library(car)
leveneTest(impairment ~ Coating, data=lenses)

# 3. One-Way ANOVA
# H0: All coating means are equal (mu_A = mu_B = mu_C = mu_D)
# H1: At least one coating mean is different
model <- aov(impairment ~ Coating, data=lenses)
summary(model)

# 4. Post-hoc test (to see which is the best)
TukeyHSD(model)

