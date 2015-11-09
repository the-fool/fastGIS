library(raster)
library(rgdal)
library(foreign)
Pts <- read.dbf(file="Samples_Bands.dbf")
Lin.grid <- raster("boundary2.img")
Lin.grid
coordinates(Lin.grid)[!is.na(values(Lin.grid)),]
Lin.grid <- SpatialPixels(SpatialPoints(coordinates(Lin.grid)[!is.na(values(Lin.grid)),]))
proj4string(Lin.grid)=CRS("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=0,0,0,0,0,0,0 +units=m +no_defs")

# Traditional Statistic exploration
d <- density(Pts$CDENSITY)
plot(d, main="Kernel Density of Carbon Density Samples")
polygon(d, col="blue")
# Q-Q plot
qqnorm(Pts$CDENSITY, main="Normal Q-Q Plot of Carbon Density Samples")
qqline(Pts$CDENSITY, col=2)
# log transformation and add 0.0001 to zero
d <- density(Pts$Log_CD)
plot(d, main="Kernel Density of Carbon Density Samples")
polygon(d, col="blue")
# Q-Q plot
qqnorm(Pts$Log_CD, main="Normal Q-Q Plot of Carbon Density Samples")
qqline(Pts$Log_CD, col=2)

# geo-statistical exploration
require(gstat)
require(sp)
class(Pts)
coordinates(Pts) = ~X+Y
proj4string(Pts)=CRS("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=500000 +y_0=0 +ellps=krass +towgs84=0,0,0,0,0,0,0 +units=m +no_defs")
Pts
summary(Pts)
bubble(Pts, "CDENSITY",
       col=c("#00ff0088", "#00ff0088"), main = "Carbon Density")

# omini direction
Pts.vgm = variogram(CDENSITY~1, Pts)
Pts.vgm
Pts.vgm.fit = fit.variogram(Pts.vgm, model=vgm(1, "Sph", 58110, 1))
Pts.vgm.fit
plot(Pts.vgm, Pts.vgm.fit)

# directional with tolerence 45 degree start from 9.5
Pts.dir = variogram(CDENSITY~1, Pts, alpha = c(32, 77, 122, 167))
Pts.dir
Pts.dir.fit = fit.variogram(Pts.dir, model = vgm(psill=15.74, model="Sph", range=58110, nugget=279, anis=c(9.84, 0.95)))
Pts.dir.fit
plot(Pts.dir, Pts.dir.fit)

# simulation for 
print("entering krige")
lzn.condsim = krige(CDENSITY~1, Pts, Lin.grid, model = Pts.vgm.fit,
                    nmax = 30, nsim = 1) #simulation result, nsim is the simulation times
print("krige returned")
save(lzn.condsim, file = "krg.rda")
spplot(lzn.condsim, main = "indicator simulations for 4 deciles") #plot simulation result
