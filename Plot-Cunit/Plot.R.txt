library(ggplot2)
Dados <- read.table("C:\\Users\\Anderson Rafhael\\Desktop\\count.txt", 
                    col.names = c("MAX", "CompLista", "CompÁrvore"), header = F)
ggplot(data = Dados) +
  geom_point(mapping = aes(x = MAX, y = CompLista), color = "red") +
  ggtitle("Comparações em uma Lista")

ggsave("CompList.pdf", plot = last_plot(), device = "pdf", 
       path = "C:\\Users\\Anderson Rafhael\\Desktop\\Plot",
       scale = 1, width = 15, height = 7, units = "cm",
       dpi = 300 )


library(ggplot2)
Dados <- read.table("C:\\Users\\Anderson Rafhael\\Desktop\\count.txt", 
                    col.names = c("MAX", "CompLista", "CompÁrvore"), header = F)
ggplot(data = Dados) +
  geom_point(mapping = aes(x = MAX, y = CompÁrvore), color = "blue2") +
  ggtitle("Comparações em uma Árvore de busca binária")

ggsave("CompTree.pdf", plot = last_plot(), device = "pdf", 
       path = "C:\\Users\\Anderson Rafhael\\Desktop\\Plot",
       scale = 1, width = 15, height = 7, units = "cm",
       dpi = 300 )
       
