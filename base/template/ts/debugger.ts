namespace Base {
	export namespace Common {

		type DebugData									= { network: DebugNetwork, post: DebugVar[], get: DebugVar[], files: DebugVar[], variables: DebugVar[], queries: DebugQuery[], controllers: DebugController[], models: DebugModule[], timestamps: DebugTimestamp[], user: DebugUser };

		type DebugNetwork								= { area: string, part: string, point: string, type: string, href: string, ip: string };
		type DebugVar									= { title: string, var: DebugVariable};
		type DebugQuery									= string;
		type DebugController							= { name: string, file: string };
		type DebugModule								= { name: string, file: string };
		type DebugTimestamp								= { name: string, time: number, start: number, stop: number };
		type DebugUser									= { name: string };

		type DebugVariable								= DebugInteger | DebugDouble | DebugString | DebugNull | DebugArray | DebugObject;

		type DebugInteger								= { type: 'integer', value: number };
		type DebugDouble								= { type: 'double', value: number };
		type DebugString								= { type: 'string', value: string };
		type DebugNull									= { type: 'null', value: null };
		type DebugArray									= { type: 'array', value: DebugArrayContent[] };
		type DebugObject								= { type: 'object', value: DebugObjectContent };

		type DebugArrayContent							= { key: DebugArrayKey, value: DebugVariable };
		type DebugArrayKey								= { type: 'integer', value: number } | { type: 'double', value: number } | { type: 'string', value: string };

		type DebugObjectContent							= { namespace: string, name: string, modifiers: DebugObjectModifier[], constants: DebugObjectConstant[], properties: DebugObjectProperty[], methods: DebugObjectMethod[] };
		type DebugObjectConstant						= { modifiers: DebugObjectConstantsModifier[], name: string, value: DebugVariable };
		type DebugObjectProperty						= { modifiers: DebugObjectPropertiesModifier[], name: string, value: DebugVariable };
		type DebugObjectMethod							= { modifiers: DebugObjectMethodsModifier[], name: string };

		type DebugObjectModifier						= 'abstract' | 'implicit' | 'explicit' | 'final' | 'readonly';
		type DebugObjectConstantsModifier				= 'public' | 'protected' | 'private' | 'final';
		type DebugObjectPropertiesModifier				= 'public' | 'protected' | 'private' | 'static' | 'readonly';
		type DebugObjectMethodsModifier					= 'public' | 'protected' | 'private' | 'final' | 'static' | 'abstract';

		export class Debugger {
			private static iter							: number;
			private static open							: boolean;
			private static data							: { [key: number]: DebugData };
			private static dataActive					: number;
			private static spaces						: { network: SNetwork, post: SVariables, get: SVariables, files: SVariables, variables: SVariables, queries: SQueries, controllers: SControllers, models: SModels, timestamps: STimestamps, user: SUser };
			private static spaceActive					: string;
			private static record						: boolean;
			private static track						: boolean;

			private static $receiver					: HTMLElement;
			private static $container					: HTMLElement;
			private static $manager						: HTMLElement;
			private static $toggle						: HTMLElement;
			private static $setting						: HTMLElement;
			private static $s_record					: HTMLElement;
			private static $s_track						: HTMLElement;
			private static $s_clear						: HTMLElement;
			private static $work						: HTMLElement;
			private static $drag						: HTMLElement;
			private static $spaces						: HTMLElement;
			private static $panel						: HTMLElement;
			private static $btns = {
				network: null,
				post: null,
				get: null,
				files: null,
				variables: null,
				queries: null,
				controllers: null,
				models: null,
				timestamps: null,
				user: null
			};

			public static Initialization(): void {
				Debugger.iter							= 1;
				Debugger.open							= (localStorage.getItem('debug_open') === '1');
				Debugger.data							= {};
				Debugger.dataActive						= 0;
				Debugger.spaceActive					= '';
				Debugger.record							= (localStorage.getItem('debug_record') !== '0');
				Debugger.track							= (localStorage.getItem('debug_track') !== '0');

				Debugger.$receiver						= document.body;
				Debugger.$container						= document.createElement('div');
				Debugger.$manager						= document.createElement('div');
				Debugger.$toggle						= document.createElement('div');
				Debugger.$setting						= document.createElement('div');
				Debugger.$s_record						= document.createElement('a');
				Debugger.$s_track						= document.createElement('a');
				Debugger.$s_clear						= document.createElement('a');
				Debugger.$work							= document.createElement('div');
				Debugger.$drag							= document.createElement('div');
				Debugger.$spaces						= document.createElement('div');
				Debugger.$panel							= document.createElement('div');
				Debugger.$btns.network					= document.createElement('a');
				Debugger.$btns.post						= document.createElement('a');
				Debugger.$btns.get						= document.createElement('a');
				Debugger.$btns.files					= document.createElement('a');
				Debugger.$btns.variables				= document.createElement('a');
				Debugger.$btns.queries					= document.createElement('a');
				Debugger.$btns.controllers				= document.createElement('a');
				Debugger.$btns.models					= document.createElement('a');
				Debugger.$btns.timestamps				= document.createElement('a');
				Debugger.$btns.user						= document.createElement('a');

				Debugger.$container.className			= 'debugger';
				Debugger.$manager.className				= 'manager';
				Debugger.$toggle.className				= 'toggle';
				Debugger.$setting.className				= 'setting';
				Debugger.$s_record.className			= 'record';
				Debugger.$s_track.className				= 'track';
				Debugger.$s_clear.className				= 'clear';
				Debugger.$work.className				= 'work hide';
				Debugger.$drag.className				= 'drag';
				Debugger.$spaces.className				= 'spaces';
				Debugger.$panel.className				= 'panel';
				if (Debugger.record) Debugger.$s_record.classList.add('active');
				if (Debugger.track) Debugger.$s_track.classList.add('active');

				Debugger.$btns.network.innerText		= 'Сеть';
				Debugger.$btns.post.innerText			= 'POST';
				Debugger.$btns.get.innerText			= 'GET';
				Debugger.$btns.files.innerText			= 'FILES';
				Debugger.$btns.variables.innerText		= 'Переменные';
				Debugger.$btns.queries.innerText		= 'Запросы';
				Debugger.$btns.controllers.innerText	= 'Контроллеры';
				Debugger.$btns.models.innerText			= 'Модели';
				Debugger.$btns.timestamps.innerText		= 'Отметки времени';
				Debugger.$btns.user.innerText			= 'Пользователь';

				Debugger.$receiver.append(Debugger.$container);
				Debugger.$container.append(Debugger.$manager, Debugger.$work);
				Debugger.$manager.append(Debugger.$toggle, Debugger.$setting);
				Debugger.$setting.append(Debugger.$s_record, Debugger.$s_track, Debugger.$s_clear);
				Debugger.$work.append(Debugger.$drag, Debugger.$spaces, Debugger.$panel);
				Debugger.$panel.append(
					Debugger.$btns.network,
					Debugger.$btns.post,
					Debugger.$btns.get,
					Debugger.$btns.files,
					Debugger.$btns.variables,
					Debugger.$btns.queries,
					Debugger.$btns.controllers,
					Debugger.$btns.models,
					Debugger.$btns.timestamps,
					Debugger.$btns.user
				);

				Debugger.$toggle.addEventListener('click', Debugger.ToggleSpase);
				Debugger.$s_record.addEventListener('click', Debugger.ToggleRecord);
				Debugger.$s_track.addEventListener('click', Debugger.ToggleTrack);
				this.$btns.network.addEventListener('click', () => Debugger.OpenSpace('network'));
				this.$btns.post.addEventListener('click', () => this.OpenSpace('post'));
				this.$btns.get.addEventListener('click', () => this.OpenSpace('get'));
				this.$btns.files.addEventListener('click', () => this.OpenSpace('files'));
				this.$btns.variables.addEventListener('click', () => this.OpenSpace('variables'));
				this.$btns.queries.addEventListener('click', () => Debugger.OpenSpace('queries'));
				this.$btns.controllers.addEventListener('click', () => Debugger.OpenSpace('controllers'));
				this.$btns.models.addEventListener('click', () => Debugger.OpenSpace('models'));
				this.$btns.timestamps.addEventListener('click', () => Debugger.OpenSpace('timestamps'));
				this.$btns.user.addEventListener('click', () => Debugger.OpenSpace('user'));
				Debugger.$s_clear.addEventListener('click', () => Debugger.ClearAll());
				Debugger.$drag.onpointerdown = event => {
					Debugger.$drag.setPointerCapture(event.pointerId);

					let clientYDown = event.clientY;
					let heightDown = Debugger.$spaces.offsetHeight;
					let maxHeight = 500;
					let minHeight = 100;

					Debugger.$drag.onpointermove = event => {
						let alpha = clientYDown - event.clientY;

						let height = heightDown + alpha;
						if (height < minHeight) height = minHeight;
						if (height > maxHeight) height = maxHeight;

						Debugger.$spaces.style.height = `${height}px`;
					};

					Debugger.$drag.onpointerup = () => {
						localStorage.setItem('debug_height', parseInt(Debugger.$spaces.style.height).toString());
						Debugger.$drag.onpointermove = null;
						Debugger.$drag.onpointerup = null;
					};
				};

				Debugger.spaces = {
					network: new SNetwork(Debugger.$spaces),
					post: new SVariables(Debugger.$spaces),
					get: new SVariables(Debugger.$spaces),
					files: new SVariables(Debugger.$spaces),
					variables: new SVariables(Debugger.$spaces),
					queries: new SQueries(Debugger.$spaces),
					controllers: new SControllers(Debugger.$spaces),
					models: new SModels(Debugger.$spaces),
					timestamps: new STimestamps(Debugger.$spaces),
					user: new SUser(Debugger.$spaces)
				};

				this.OpenSpace(localStorage.getItem('debug_open_space') || 'network');

				let debug_height = localStorage.getItem('debug_height');
				this.$spaces.style.height = debug_height ? `${debug_height}px` : `200px`;
				if (Debugger.open) Debugger.$work.classList.remove('hide');
			}

			public static Append(data: DebugData): void {
				if (!Debugger.record) return;
				Debugger.data[Debugger.iter] = data;
				Debugger.spaces['network'].Set(data['network'], Debugger.iter);
				if (Debugger.track) Debugger.Load(Debugger.iter);
				Debugger.iter++;
			}

			public static Load(iter: number): void {
				Debugger.spaces['post'].Clear().Set(Debugger.data[iter]['post']);
				Debugger.spaces['get'].Clear().Set(Debugger.data[iter]['get']);
				Debugger.spaces['files'].Clear().Set(Debugger.data[iter]['files']);
				Debugger.spaces['variables'].Clear().Set(Debugger.data[iter]['variables']);
				Debugger.spaces['queries'].Clear().Set(Debugger.data[iter]['queries']);
				Debugger.spaces['controllers'].Clear().Set(Debugger.data[iter]['controllers']);
				Debugger.spaces['models'].Clear().Set(Debugger.data[iter]['models']);
				Debugger.spaces['timestamps'].Clear().Set(Debugger.data[iter]['timestamps']);
				Debugger.spaces['user'].Clear().Set(Debugger.data[iter]['user']);
			}

			private static ToggleSpase(): void {
				Debugger.open = !Debugger.open;
				localStorage.setItem('debug_open', Debugger.open ? '1' : '0');
				Debugger.open ? Debugger.$work.classList.remove('hide') : Debugger.$work.classList.add('hide');
			}

			private static ToggleRecord(): void {
				Debugger.record = !Debugger.record;
				localStorage.setItem('debug_record', Debugger.record ? '1' : '0');
				Debugger.record ? Debugger.$s_record.classList.add('active') : Debugger.$s_record.classList.remove('active');
			}

			private static ToggleTrack(): void {
				Debugger.track = !Debugger.track;
				localStorage.setItem('debug_track', Debugger.track ? '1' : '0');
				Debugger.track ? Debugger.$s_track.classList.add('active') : Debugger.$s_track.classList.remove('active');
			}

			private static OpenSpace(name: string): void {
				if (name === this.spaceActive) return;

				if (this.spaceActive) {
					this.$btns[this.spaceActive].classList.remove('active');
					this.spaces[this.spaceActive].Hide();
				}

				this.$btns[name].classList.add('active');
				this.spaces[name].Show();

				this.spaceActive = name;
				localStorage.setItem('debug_open_space', name);
			}

			private static ClearAll() {
				Debugger.spaces['network'].Clear();
				Debugger.spaces['post'].Clear();
				Debugger.spaces['get'].Clear();
				Debugger.spaces['files'].Clear();
				Debugger.spaces['variables'].Clear();
				Debugger.spaces['queries'].Clear();
				Debugger.spaces['controllers'].Clear();
				Debugger.spaces['models'].Clear();
				Debugger.spaces['timestamps'].Clear();
				Debugger.spaces['user'].Clear();
				Debugger.data = {};
				Debugger.iter = 1;
			}

		}

		abstract class Space {
			$space										: HTMLElement;

			protected constructor($spaces: HTMLElement) {
				this.$space								= document.createElement('div');

				this.Hide();
				$spaces.append(this.$space);
			}

			protected PrepareData(data: any): any { return data; }

			abstract Set(data: any, iter?: number): void;
			abstract Clear(): Space;

			public Hide(): void { this.$space.classList.add('hide'); }
			public Show(): void { this.$space.classList.remove('hide'); }

		}

		abstract class STable extends Space {
			cols										: {[key: string]: string};
			$wrap										: HTMLElement;
			$head										: HTMLElement;

			protected constructor($spaces: HTMLElement, cols: {[key: string]: string}) {
				super($spaces);

				this.cols								= cols;

				this.$wrap								= document.createElement('div');
				this.$head								= document.createElement('div');

				this.$wrap.classList.add('table');
				this.$head.classList.add('head');

				this.$space.append(this.$wrap);
				this.$wrap.append(this.$head);

				for (const col in this.cols) this.$head.append(
					this.GetItem(this.cols[col])
				);
			}

			protected GetItem(text: string): HTMLElement {
				let $item								= document.createElement('div');
				$item.innerText = text;

				return $item;
			}

			public Set(data: any, iter?: number): void {
				let prepareData = this.PrepareData(data);
				for (const i in prepareData) {
					let $line							= document.createElement('div');

					$line.classList.add('line');

					this.$wrap.append($line);
					for (const col in this.cols) $line.append(
						this.GetItem(prepareData[i][col])
					);
				}
			}

			public Clear(): Space {
				let elements = this.$wrap.getElementsByClassName('line');
				while (elements.length) elements[0].parentNode.removeChild(elements[0]);

				return this;
			}

		}

		class SNetwork extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'area': 'Страница', 'part': 'Действие', 'point': 'Точка входа', 'type': 'Тип', 'href': 'URL', 'ip': 'IP'});
			}

			public Set(data: DebugNetwork, iter: number): void {
				let $line								= document.createElement('div');
				$line.classList.add('line', 'link');

				this.$wrap.append($line);

				for (const col in this.cols) $line.append(
					this.GetItem(data[col])
				);

				$line.addEventListener('click', () => { Debugger.Load(iter); });
			}

		}

		class SControllers extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'name': 'Имя', 'file': 'Файл'});
			}

		}

		class SModels extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'name': 'Имя', 'file': 'Файл'});
			}

		}

		class SQueries extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'number': '№', 'query': 'Запрос'});
			}

			protected PrepareData(data: DebugQuery[]): any {
				let out = [];
				for (const i in data) out.push({'number': Number(i) + 1, 'query': data[i]});

				return out;
			}

		}

		class STimestamps extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'name': 'Имя', 'time': 'Время (мс.)', 'start': 'Начало', 'stop': 'Конец'});
			}

		}

		class SUser extends STable {

			public constructor($spaces: HTMLElement) {
				super($spaces, {'param': 'Параметр', 'value': 'Значение'});
			}

			protected PrepareData(data: DebugUser): any {
				return [{'param': 'Имя', 'value': data['name']}];
			}

		}

		class SVariables extends Space {

			public constructor($spaces: HTMLElement) {
				super($spaces);
			}

			public Set(data: DebugVar[]): void {
				for (const datum of data) {
					let $dump							= document.createElement('div');
					let $title							= document.createElement('div');
					let $content						= document.createElement('div');

					$dump.classList.add('dump');
					$title.classList.add('title');
					$content.classList.add('content');

					$title.innerText = datum['title'];

					$content.append(this.Parsing(datum['var']));
					$dump.append($title, $content);
					this.$space.append($dump);
				}
			}

			public Clear(): Space {
				this.$space.innerText = '';
				return this;
			}

			public Parsing(data: DebugVariable): HTMLElement {
				let $var						= document.createElement('div');
				let $type						= document.createElement('div');
				let $value						= document.createElement('div');

				$var.classList.add('variable', data['type']);
				$type.classList.add('type');
				$value.classList.add('value');

				$type.innerText = data['type'];

				switch (data['type']) {
					case 'integer': case 'double': $value.innerText = data['value'].toString(); break;
					case 'string': $value.innerText = data['value']; break;
					case 'null': $value.innerText = 'null'; break;
					case 'array': $value.append(this.GetArray(data['value'])); break;
					case 'object': $value.append(this.GetObject(data['value'])); break;
				}

				$var.append($type, $value);

				return $var;
			}

			private GetArray(elems: DebugArrayContent[]): DocumentFragment {
				let $collection = document.createDocumentFragment();

				let $more							= document.createElement('div');
				let $elems							= document.createElement('div');

				$more.classList.add('more');
				$elems.classList.add('elems');
				$more.addEventListener('click', () => { $more.classList.toggle('open'); });

				$collection.append($more, $elems);

				for (const elem of elems) {
					let $elem						= document.createElement('div');
					let $key						= document.createElement('div');
					let $index						= document.createElement('span');
					let $value						= document.createElement('div');

					$key.classList.add('key');
					$value.classList.add('value');

					if (elem['key']['type'] == 'string') {
						$key.classList.add('string');
						$index.innerText = `'${elem['key']['value']}'`;
					} else {
						$key.classList.add('number');
						$index.innerText = elem['key']['value'].toString();
					}
					$key.append(`[ `, $index , ` ]`);

					$elem.append($key, $value);
					$value.append(this.Parsing(elem['value']));

					$elems.append($elem);
				}

				return $collection;
			}

			private GetObject(obj: DebugObjectContent): DocumentFragment {

				function GetElem(key: string, value: string) {
					let $elem						= document.createElement('div');
					let $icon						= document.createElement('div');
					let $value						= document.createElement('div');

					$elem.classList.add(key);
					$icon.classList.add('icon');
					$value.innerText = value;

					$elem.append($icon, $value);

					return $elem;
				}

				function GetConstant(constant: DebugObjectConstant, $value: HTMLElement) {
					let $elem						= document.createElement('div');
					let $icon						= document.createElement('div');
					let $name						= document.createElement('div');

					$icon.classList.add('icon');
					$name.classList.add('name');
					if (constant['modifiers'].includes('public')) $icon.classList.add('public');
					if (constant['modifiers'].includes('protected')) $icon.classList.add('protected');
					if (constant['modifiers'].includes('private')) $icon.classList.add('private');
					if (constant['modifiers'].includes('final')) $icon.classList.add('final');

					$name.innerText = constant['name'];

					$elem.append($icon, $name, $value);

					return $elem;
				}

				function GetProperty(property: DebugObjectProperty, $value: HTMLElement) {
					let $elem						= document.createElement('div');
					let $icon						= document.createElement('div');
					let $name						= document.createElement('div');

					$icon.classList.add('icon');
					$name.classList.add('name');
					if (property['modifiers'].includes('public')) $icon.classList.add('public');
					if (property['modifiers'].includes('protected')) $icon.classList.add('protected');
					if (property['modifiers'].includes('private')) $icon.classList.add('private');
					if (property['modifiers'].includes('static')) $icon.classList.add('static');
					if (property['modifiers'].includes('readonly')) $icon.classList.add('readonly');

					$name.innerText = property['name'];

					$elem.append($icon, $name, $value);

					return $elem;
				}

				function GetMethod(method: DebugObjectMethod) {
					let $elem						= document.createElement('div');
					let $icon						= document.createElement('div');
					let $name						= document.createElement('div');

					$icon.classList.add('icon');
					if (method['modifiers'].includes('public')) $icon.classList.add('public');
					if (method['modifiers'].includes('protected')) $icon.classList.add('protected');
					if (method['modifiers'].includes('private')) $icon.classList.add('private');
					if (method['modifiers'].includes('static')) $icon.classList.add('static');
					if (method['modifiers'].includes('final')) $icon.classList.add('final');
					if (method['modifiers'].includes('abstract')) $icon.classList.add('abstract');

					$name.innerText = method['name'];

					$elem.append($icon, $name);

					return $elem;
				}

				let $collection = document.createDocumentFragment();

				let $more							= document.createElement('div');
				let $info							= document.createElement('div');

				$more.classList.add('more');
				$info.classList.add('info');

				$more.addEventListener('click', () => { $more.classList.toggle('open'); });

				$info.append(GetElem('namespace', obj['namespace']));
				$info.append(GetElem('class', obj['name']));

				let $constants = document.createElement('div');
				$constants.classList.add('constants');
				for (const constant of obj['constants']) $constants.append(GetConstant(constant, this.Parsing(constant['value'])));
				$info.append($constants);

				let $properties = document.createElement('div');
				$properties.classList.add('properties');
				for (const property of obj['properties']) $properties.append(GetProperty(property, this.Parsing(property['value'])));
				$info.append($properties);

				let $methods = document.createElement('div');
				$methods.classList.add('methods');
				for (const method of obj['methods']) $methods.append(GetMethod(method));
				$info.append($methods);

				$collection.append($more, $info);

				return $collection;
			}

		}

	}
}