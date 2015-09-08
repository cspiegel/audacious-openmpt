OBJS=		$(SRCS:%.cpp=%.o)

PKG+=		audacious

ifneq ($(shell pkg-config $(PKG) > /dev/null 2>&1 ; echo $$?),0)
  $(error "Cannot find all packages: $(PKG)")
endif

CXXFLAGS+=	$(shell pkg-config $(PKG) --cflags) -g -DPACKAGE='"$(TARGET)"'
LDADD=		$(shell pkg-config $(PKG) --libs)
PLUGDIR=	$(shell pkg-config audacious --var=plugin_dir)/Input

%.o: %.cpp
	$(CXX) $(OPT) $(CXXFLAGS) -fPIC -c $< -o $@

all: $(TARGET).so

$(TARGET).so: $(OBJS)
	$(CXX) $(OPT) -shared $^ -o $@ $(LDADD)

clean:
	rm -f *.o *.so

install: $(TARGET).so
	mkdir -p $(DESTDIR)$(PLUGDIR)
	install -m755 $^ $(DESTDIR)$(PLUGDIR)
