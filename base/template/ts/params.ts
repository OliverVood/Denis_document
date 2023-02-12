namespace Base {
	export namespace Common {

		export class GlobalParams {
			private static param = {};

			public static Set(name :string, value :any) {
				GlobalParams.param[name] = value;
			}

			public static Get(name) :any {
				return GlobalParams.param[name];
			}

		}

	}
}