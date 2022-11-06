namespace Admin {
	export namespace Common {

		class Section {
			private $_elem			: JQuery

			public constructor($_elem: JQuery) {
				this.$_elem = $_elem;
			}

			public Fill(...contents) {
				this.$_elem.empty();
				for (let i in contents) {
					if (Array.isArray(contents[i])) for (let j in contents[i]) this.$_elem.append(contents[i][j]);
					else this.$_elem.append(contents[i]);
				}
			}

			public Push(...contents) {
				for (let i in arguments) {
					if (Array.isArray(arguments[i])) for (let j in arguments[i]) this.$_elem.append(arguments[i][j]);
					else this.$_elem.append(arguments[i])
				}
			}

		}

		export class Layout {
			public static header	: Section;
			public static menu		: Section;
			public static main		: Section;
			public static footer	: Section;

			public static Initialization() {
				Layout.header = new Section($('header'));
				Layout.menu = new Section($('menu'));
				Layout.main = new Section($('main'));
				Layout.footer = new Section($('footer'));
			}

		}

	}
}