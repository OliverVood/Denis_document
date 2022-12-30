namespace Site {
	export namespace Common {

		export class Layout extends Base.Common.Layout {
			public static header: Base.Common.Section;
			public static main: Base.Common.Section;
			public static footer: Base.Common.Section;

			public static Initialization(): void {
				Layout.header = new Base.Common.Section($('header'));
				Layout.main = new Base.Common.Section($('main'));
				Layout.footer = new Base.Common.Section($('footer'));
			}

		}

	}
}