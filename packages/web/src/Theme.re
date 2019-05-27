module Colors = {
  /* Brand */
  let balticSea = `hsl((258, 10, 18)); /* rgb(44, 41, 51) - #2c2933 */
  let smoky = `hsl((258, 10, 38)); /* rgb(93, 87, 107) - #5d576b */
  let manatee = `hsl((258, 10, 58)); /* rgb(143, 137, 159) - #8f899f */
  let graySuit = `hsl((258, 10, 88)); /* rgb(197, 193, 205) - #c5c1cd */

  /* Grayscale */
  let black = `hsl((0, 0, 0)); /* rgb(0, 0, 0) - #000000 */
  let doveGray = `hsl((0, 0, 44)); /* rgb(112, 112, 112) - #707070 */
  let silver = `hsl((0, 0, 80)); /* rgb(205, 205, 205) - #cdcdcd */
  let white = `hsl((0, 0, 100)); /* rgb(255, 255, 255) - #ffffff */

  /* Red/Yellows */
  let guardsmanRed = `hsl((0, 100, 40)); /* rgb(204, 0, 0) - #cc0000 */
  let clementine = `hsl((28, 98, 47)); /* rgb(237, 113, 2) - #ed7102 */
  let schoolBusYellow = `hsl((52, 100, 50)); /* rgb(255, 221, 0) - #ffdd00 */

  /* Greens */
  let puertoRico = `hsl((162, 44, 52)); /* rgb(80, 187, 155) - #50bb9b */
  let persianGreen = `hsl((176, 100, 34)); /* rgb(0, 171, 159) - #00ab9f */

  /* Blues */
  let iron = `hsl((206, 12, 88)); /* rgb(222, 226, 229) - #dee2e5 */
  let chathamsBlue = `hsl((218, 9, 45)); /* rgb(23, 66, 139) - #17428b */
  let botticelli = `hsl((224, 30, 88)); /* rgb(214, 219, 233) - #d6dbe9 */
  let whiteLilac = `hsl((225, 40, 94)); /* rgb(234, 237, 246) - #3aedf6 */
  let athensGray = `hsl((240, 23, 97)); /* rgb(247, 247, 250) - #f7f7fa */
  let whisper = `hsl((240, 33, 99)); /* rgb(251, 251, 253) - #fbfbfd */

  /* Purples */
  let eminence = `hsl((285, 45, 29)); /* rgb(91, 41, 107) - #5b296b */
  let prim = `hsl((300, 33, 98)); /* rgb(252, 248, 252) - #fcf8fc */

  let shadow = `rgba((128, 152, 213, 0.075));

  let opacity = (~color, ~opacity as a) => {
    switch (color) {
    | `rgb(r, g, b) => `rgba((r, g, b, a))
    | `hsl(h, s, l) => `hsla((h, s, l, a))
    };
  };
};

module Typography = {
  type t = [
    | `XXSmall
    | `XSmall
    | `Small
    | `Medium
    | `Large
    | `Heading1
    | `Heading2
  ];

  let fontSize = fontVariant =>
    switch (fontVariant) {
    | `XXSmall => `px(12)
    | `XSmall => `px(14)
    | `Small => `px(16)
    | `Medium => `px(18)
    | `Large => `px(21)
    | `Heading1 => `px(60)
    | `Heading2 => `px(32)
    | `Heading3 => `px(18)
    };

  let fontStack = "'Alte Haas Grotesk', sans-serif";
};
