namespace Admin {
	export namespace Common {

		export class Layout extends Base.Common.Layout {
			public static header	: Base.Common.Section;
			public static menu		: Base.Common.Section;
			public static main		: Base.Common.Section;
			public static footer	: Base.Common.Section;

			public static Initialization() {
				Layout.header = new Base.Common.Section($('header'));
				Layout.menu = new Base.Common.Section($('menu'));
				Layout.main = new Base.Common.Section($('main'));
				Layout.footer = new Base.Common.Section($('footer'));
			}

		}

	}
}