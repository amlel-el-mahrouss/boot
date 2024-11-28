/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <lib/pci_express.h>
#include <lib/memory_map.h>
#include <lib/string.h>

#define PCI_ROOT "/@/"
#define PCI_TREE PCI_ROOT "pci/"

static struct hw_pci_tree* g_base_tree = nil;
static struct hw_pci_tree* g_latest_tree = nil;
static struct hw_pci_tree* g_last_tree = nil;

/// Init the PCI device tree structure.
/// \return if it already exists -> false
/// Otherwise true.
boolean pci_init_tree(void)
{
    g_base_tree = (struct hw_pci_tree*)g_memmap[HW_MEMMAP_PCI_TREE].base_ptr;

    // huh? anyway let's ignore it then.
    if (g_base_tree->d_magic == SYS_PCI_DEV_MAGIC)
    {
        panic("[pci] invalid pci device.\n");
        return no;
    }

    g_base_tree->d_magic = SYS_PCI_DEV_MAGIC;

    memncpy(g_base_tree->d_name, PCI_TREE, strlen(PCI_TREE));

    g_base_tree->d_next_sibling = 0;
    g_base_tree->d_off_props = 0;
    g_base_tree->d_sz_struct = 0;
    g_base_tree->d_sz_props = 0;
    g_base_tree->d_off_struct = 0;
    g_base_tree->d_version = SYS_PCI_VERSION;

    g_base_tree->d_next_sibling = (pci_num_t)(g_base_tree + sizeof(struct hw_pci_tree));
    g_base_tree->d_first_node = (pci_num_t)g_base_tree;

    return yes;
}

/// adds a new device to the tree.
/// \param name the device name.
/// \param struct_ptr the struct containing the device.
/// \param struct_sz the structure size.
boolean pci_add_tree(const caddr_t name, pci_num_t struct_ptr, pci_num_t struct_sz)
{
    if (!name ||
        *name == 0)
        return no;

    struct hw_pci_tree* pci_tree = (struct hw_pci_tree*)(g_latest_tree + sizeof(struct hw_pci_tree));

    pci_tree->d_magic = SYS_PCI_DEV_MAGIC;
    memncpy(pci_tree->d_name, name, strlen(name));
    pci_tree->d_off_struct = struct_ptr;
    pci_tree->d_sz_struct = struct_sz;
    pci_tree->d_off_props = 0;
    pci_tree->d_sz_props = 0;
    pci_tree->d_version = SYS_PCI_VERSION;

    pci_tree->d_next_sibling = (pci_num_t)(pci_tree + sizeof(struct hw_pci_tree));
    pci_tree->d_first_node = (pci_num_t)pci_tree;

    g_latest_tree = pci_tree;
    g_last_tree = pci_tree;

    return yes;
}