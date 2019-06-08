module Colors = {
  /* Brand */
  let balticSea = `hsl((258, 10, 18)); /* rgb(44, 41, 51) - #2c2933 */
  let smoky = `hsl((258, 10, 38)); /* rgb(93, 87, 107) - #5d576b */
  let manatee = `hsl((258, 10, 58)); /* rgb(143, 137, 159) - #8f899f */
  let graySuit = `hsl((258, 10, 88)); /* rgb(197, 193, 205) - #c5c1cd */

  let athensGray = `hsl((240, 23, 97)); /* rgb(247, 247, 250) - #f7f7fa */
  let whisper = `hsl((252, 29, 97)); /*	rgb(245, 244, 249) - #f5f4f9 */

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

  let fontStack = "-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto,
  Helvetica, Arial, sans-serif, 'Apple Color Emoji', 'Segoe UI Emoji', 'Segoe UI
    Symbol'";
};
