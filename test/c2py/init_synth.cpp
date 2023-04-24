
// maker ...

// if default constructible. If not error ....
// if no element is private
// SOME CHECK or I can not do it ...
// FIXME : what if Cls is template ??

Cls maker(c2py::pydict kw) {
  Cls self;
  pydict_extractor de{kw};
  de(self.i, "i", err);
  de(self.x, "x", err, true); // optional
  de(self.v, "v", err);
  return self;
};

c2py::pydict as_python_dict(Cls const &x) {
  c2py::pydict dic;
  dic["i"] = self.i;
  dic["x"] = self.x;
  dic["v"] = self.v;
  dic["w"] = self.w;
  return dic;
}
