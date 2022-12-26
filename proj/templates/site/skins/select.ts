namespace Skins {

	export class Select {

		constructor(elem: string | JQuery, funcDelete: Function | null = null) {
			let $elem = (typeof elem === 'string') ? $(elem) : elem;

			$elem.hide();
			let $skin = $('<div>', {class: 'skin select'});
			let $placeholder = $('<div>', {class: 'placeholder'});
			let $content = $('<div>', {class: 'content'});

			this.ScanElem($elem, $content, funcDelete);

			$skin.append(
				$placeholder.text('Выберите'),
				$content
			)

			$elem.after($skin);
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
			let $wrap = $('<div/>', {class: `option${selected}${disabled}${hidden}`});
			let $option = $('<div/>', {class: 'select'});
			let $delete = $('<div/>', {class: 'delete'});

			/* Building DOM */
			$wrap.append(
				$option,
				funcDelete ? $delete : $()
			);

			/* Events */
			$option.on('click', () => $elem.trigger('change'));
			if (funcDelete) $delete.on('click', () => funcDelete(value));

			$option.text(text);

			$parent.append($wrap);
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
			)

			$parent.append($optgroup);
		}

	}

}