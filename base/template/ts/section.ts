namespace Base {
	export namespace Common {

		export class Section {
			private $_elem: JQuery

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

	}
}