namespace Skins {

	export class Select {
		/* Variables */
		open									: boolean;
		closing									: boolean;

		/* Elements */
		private readonly $elem					: JQuery;
		private readonly $skin					: JQuery;
		private readonly $placeholder			: JQuery;
		private readonly $content				: JQuery;
		private readonly funcDelete				: Function | null;
		private readonly data					: Object;

		constructor(elem: string | JQuery, funcDelete: Function | null = null, data: Object = {}) {
			/* Set variables */
			this.open			= false;
			this.closing		= true;
			this.funcDelete		= funcDelete;
			this.data			= data;

			/* Set elements */
			this.$elem = (typeof elem === 'string') ? $(elem) : elem;
			this.$skin = $('<div>', {tabindex: 0, class: 'skin select'});
			this.$placeholder = $('<div>', {class: 'placeholder'});
			this.$content = $('<div>', {class: 'content'});

			/* Events */
			this.$skin.on('click', this.OnSkin.bind(this));
			this.$placeholder.on('click', this.Switch.bind(this));
			$(document).on('click', this.OnDocument.bind(this));

			this.ScanElem(this.$elem, this.$content, this.funcDelete, this.data);

			this.$elem.hide();

			this.$skin.append(
				this.$placeholder,
				this.$content
			);

			this.$elem.after(this.$skin);

			let observer = new MutationObserver(this.Restructure.bind(this));

			observer.observe(this.$elem[0], {childList: true});
		}

		private Restructure(record: MutationRecord[], obs: MutationObserver): void {
			this.$content.empty();
			this.$placeholder.text('Выберите');
			this.ScanElem(this.$elem, this.$content, this.funcDelete, this.data);
			console.log(record, obs);
		}

		private OnSkin(): void {
			this.closing = false;
		}

		private OnDocument(): void {
			if (this.closing) this.Close();
			this.closing = true;
		}

		private Switch(): void {
			switch (this.open) {
				case true: this.Close(); break;
				case false: this.Open(); break;
			}
		}

		private Open(): void {
			this.$skin.addClass('open');
			this.open = true;
		}

		private Close(): void {
			this.$skin.removeClass('open');
			this.open = false;
		}

		private ScanElem($elem: JQuery, $parent: JQuery, funcDelete: Function | null, data: Object = {}): void {
			let self = this;

			$elem.children().each(function(i, item) {
				let $item = $(item);
				switch ($item.prop('nodeName')) {
					case 'OPTION': self.RenderOption($item, $parent, funcDelete, data); break;
					case 'OPTGROUP': self.RenderOptgroup($item, $parent, funcDelete, data); break;
				}
			});
		}

		private RenderOption($elem: JQuery, $parent: JQuery, funcDelete: Function | null, data: Object = {}): void {
			/* Variables */
			let text = $elem.text();
			let value = $elem.attr('value');
			let selected = ($elem.is(':selected')) ? ' selected' : '';
			let disabled = ($elem.is(':disabled')) ? ' disabled' : '';
			let hidden = ($elem.is(':disabled')) ? ' hidden' : '';

			/* Elements */
			let $option = $('<div/>', {class: `option${selected}${disabled}${hidden}`});
			let $select = $('<div/>', {class: 'select'});
			let $delete = $('<div/>', {class: 'delete'});

			if ($elem.is(':checked')) this.$placeholder.text(text);

			/* Building DOM */
			$option.append(
				$select,
				funcDelete ? $delete : $()
			);

			/* Events */
			$select.on('click', () => {
				$elem.prop('selected', true);
				$elem.trigger('change');
				this.$content.children().removeClass('selected');
				$option.addClass('selected');
				this.$placeholder.text(text);
				this.Close();
			});
			if (funcDelete) $delete.on('click', () => funcDelete(Number(value), data));

			$select.text(text);

			$parent.append($option);
		}

		private RenderOptgroup($elem: JQuery, $parent: JQuery, funcDelete: Function | null, data: Object = {}): void {
			let label = $elem.attr('label');

			let $optgroup = $('<div/>', {class: 'optgroup'});
			let $label = $('<div/>', {class: 'label'});
			let $content = $('<div/>', {class: 'content'});

			this.ScanElem($elem, $content, funcDelete, data);

			$optgroup.append(
				$label.text(label),
				$content
			);

			$parent.append($optgroup);
		}

	}

}