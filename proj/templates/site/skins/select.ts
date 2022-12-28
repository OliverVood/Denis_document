namespace Skins {

	export class Select {
		/* Variables */
		open					: boolean;
		closing					: boolean;

		/* Elements */
		$skin					: JQuery;
		$placeholder			: JQuery;

		constructor(elem: string | JQuery, funcDelete: Function | null = null) {
			/* Set variables */
			this.open			= false;
			this.closing		= true;

			/* Set elements */
			this.$skin = $('<div>', {class: 'skin select'});
			this.$placeholder = $('<div>', {class: 'placeholder'});
			let $content = $('<div>', {class: 'content'});
			let $elem = (typeof elem === 'string') ? $(elem) : elem;

			/* Events */
			this.$skin.on('click', this.OnSkin.bind(this));
			this.$placeholder.on('click', this.Switch.bind(this));
			$(document).on('click', this.OnDocument.bind(this));

			this.ScanElem($elem, $content, funcDelete);

			$elem.hide();

			this.$skin.append(
				this.$placeholder,
				$content
			);

			$elem.after(this.$skin);
		}

		private OnSkin() {
			this.closing = false;
		}

		private OnDocument() {
			if (this.closing) this.Close();
			this.closing = true;
		}

		private Switch() {
			switch (this.open) {
				case true: this.Close(); break;
				case false: this.Open(); break;
			}
		}

		private Open() {
			this.$skin.addClass('open');
			this.open = true;
		}

		private Close() {
			this.$skin.removeClass('open');
			this.open = false;
		}

		private ScanElem($elem: JQuery, $parent: JQuery, funcDelete: Function | null) {
			let self = this;

			$elem.children().each(function(i, item) {
				let $item = $(item);
				switch ($item.prop('nodeName')) {
					case 'OPTION': self.RenderOption($item, $parent, funcDelete); break;
					case 'OPTGROUP': self.RenderOptgroup($item, $parent, funcDelete); break;
				}
			});
		}

		private RenderOption($elem: JQuery, $parent: JQuery, funcDelete: Function | null) {
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
				this.$placeholder.text(text);
				this.Close();
			});
			if (funcDelete) $delete.on('click', () => funcDelete(Number(value)));

			$select.text(text);

			$parent.append($option);
		}

		private RenderOptgroup($elem: JQuery, $parent: JQuery, funcDelete: Function | null) {
			let label = $elem.attr('label');

			let $optgroup = $('<div/>', {class: 'optgroup'});
			let $label = $('<div/>', {class: 'label'});
			let $content = $('<div/>', {class: 'content'});

			this.ScanElem($elem, $content, funcDelete);

			$optgroup.append(
				$label.text(label),
				$content
			);

			$parent.append($optgroup);
		}

	}

}