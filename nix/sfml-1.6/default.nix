{ lib
, stdenv
, fetchFromGitHub
, fetchpatch
, cmake
, libX11
, freetype
, libjpeg
, openal
, flac
, libvorbis
, libsndfile
, glew
, libXrandr
, libXrender
, udev
, xcbutilimage
}:

stdenv.mkDerivation rec {
  pname = "sfml";
  version = "1.6.0";

  src = fetchFromGitHub {
    owner = "SFML";
    repo = "SFML";
    rev = "1.x";
    sha256 = "sha256-HwQ9B37KqE1Pwcq6N+ayxX8GJm6kQBJJkHbx8wF050A=";
  };

  patches = [
    ./sfml-modern-gcc.patch
  ];

  buildInputs = [ freetype libjpeg openal flac libvorbis glew libsndfile ]
    ++ lib.optional stdenv.isLinux udev
    ++ lib.optionals (!stdenv.isDarwin) [ libX11 libXrandr libXrender xcbutilimage ];

  makeFlags = [ "DESTDIR=$(out)" ];

  meta = with lib; {
    homepage = "https://www.sfml-dev.org/";
    description = "Simple and fast multimedia library";
    longDescription = ''
      SFML is a simple, fast, cross-platform and object-oriented multimedia API.
      It provides access to windowing, graphics, audio and network.
      It is written in C++, and has bindings for various languages such as C, .Net, Ruby, Python.
    '';
    license = licenses.zlib;
    maintainers = [ maintainers.astsmtl ];
    platforms = platforms.unix;
  };
}
