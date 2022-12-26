namespace Skins {

	export class Select {

		constructor(elem: string | JQuery) {
			let $elem = (typeof elem === 'string') ? $(elem) : elem;

			$elem.hide();
			let $skin = $('<div>', {class: 'skin select'});
			let $placeholder = $('<div>', {class: 'placeholder'});
			let $content = $('<div>', {class: 'content'});

			this.ScanElem($elem, $content);

			$skin.append(
				$placeholder.text('Выберите'),
				$content
			)

			$elem.after($skin);
		}

		private ScanElem($elem: JQuery, $parent: JQuery) {
			let self = this;

			$elem.children().each(function(i, item) {
				let $item = $(item);
				switch ($item.prop('nodeName')) {
					case 'OPTION': self.RenderOption($item, $parent); break;
					case 'OPTGROUP': self.RenderOptgroup($item, $parent); break;
				}
			});
		}

		private RenderOption($elem: JQuery, $parent: JQuery) {
			let text = $elem.text();
			let selected = ($elem.is(':selected')) ? ' selected' : '';
			let disabled = ($elem.is(':disabled')) ? ' disabled' : '';
			let hidden = ($elem.is(':disabled')) ? ' hidden' : '';

			let $option = $('<div/>', {class: `option${selected}${disabled}${hidden}`});

			$option.on('click', () => {$elem.prop('selected', true); $elem.trigger('change'); /*console.log($elem); $elem.trigger('click');*/ });

			$option.text(text);

			$parent.append($option);
		}

		private RenderOptgroup($elem: JQuery, $parent: JQuery) {
			let label = $elem.attr('label');

			let $optgroup = $('<div/>', {class: 'optgroup'});
			let $label = $('<div/>', {class: 'label'});
			let $content = $('<div/>', {class: 'content'});

			this.ScanElem($elem, $content);

			$optgroup.append(
				$label.text(label),
				$content
			)

			$parent.append($optgroup);
		}

	}

}